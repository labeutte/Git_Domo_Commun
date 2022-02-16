/* 
 * File:   domot.cpp/main.cpp
 * Author: aucaigne
 */
#include <cstdlib>
#include <stdio.h>
#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string

#include <pthread.h>
#include "sim.h"
#include "RCSwitch.h"
#include "accesBDD.h"
#include "monitFTP.h"

using namespace std;

void traitement433(long unsigned);

/***GLOBAL***/
static pthread_mutex_t exMut;
string ttyPort1, ttyPort2;
accesBDD dataBase;
monitFTP myMonit;
SIM maSim;
RCSwitch* mySwitch;
fd_set fds;
ft RCSwitch::pft; // = alert433;
FILE* flog;
int b = 0;
int etat = 1; // état du système
int basc_a;
std::time_t tpsRebond;

/*************/

/**
 * Retourne la date au format français
 */
string dateL() {
    const char* nomJourSem[] = {"Dim", "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam"};
    const char* nomMois[] = {"janv", "fev", "mar", "avr", "mai", "juin", "juil", "aout", "sept", "oct", "nov", "dec"};

    char locTime[30];
    time_t TH;
    struct tm* t;
    TH = time(NULL);
    t = localtime(&TH);
    sprintf(locTime, "%3s %02u %s %04u %02u:%02u:%02u", nomJourSem[t->tm_wday], t->tm_mday, nomMois[t->tm_mon], 1900 + t->tm_year, t->tm_hour, t->tm_min, t->tm_sec);
    return (string(locTime));
}

/**
 * traitement433
 * @param p valeur reçu du recepteur 433
 */
void traitement433(long unsigned p) {
    int cr;
    stXm stX;

    if (std::time(0) - tpsRebond > 15) { // On attend au minimum 15s (rebond)
        tpsRebond = std::time(0);
        if (dataBase.getstate() == 1) {
            float temp, ID;
            string dt = dateL();
            ////printf("\n%s => RFreq=%lx ", dt.c_str(), p);
            if (p > 2049 && p < 65299) {
                ID = p >> 11;
                temp = ((p & 2047) / 10.0) - 56;

                if (temp != 85) {
                    ////printf("Id: %f  Temp: %f\n\n", ID, temp);
                    dataBase.updatetemp(ID, temp);
                    if (temp < dataBase.gettempalert(ID) && basc_a == 0) {
						printf("\nAlerte temp, Id: %f  Temp: %f\n\n", ID, temp);
                        dataBase.alertcapt(dataBase.getidcapt(ID));
                        stringstream ss;
                        ss << dataBase.gettempalert(ID);
                        string str = ss.str();
                        string texto = dataBase.getcaptname(ID);
                        texto += ": temperature inferieur a ";
                        texto += str;
                        texto += " degres. ";
                        texto += dateL();
                        texto += '\0';

                        stX.type = 0; //SMS
                        stX.message = texto;
                        stX.groupe = 1;
                        maSim.pushListXms(stX);
                        basc_a = 1;
                    }
                    if (temp >= dataBase.gettempalert(ID)) {
                        basc_a = 0;
                    }
                }
            }
            if (p > 65298 && p < 16777216) {
                printf("Capteur: %ld\n\n", p);
                dataBase.alertcapt(dataBase.getidcapt(p));

                string texto = dataBase.getcaptname(p);
                texto += ": alerte! ";
                texto += dateL();
                texto += '\0';
                stX.type = 0; //SMS
                stX.message = texto;
                stX.groupe = 1;
                maSim.pushListXms(stX);
            }
        }
    }
}

/**
 * routine d'interruption sur reception 433
 */

void alert433(unsigned long alert) {
    if (etat) {
        traitement433(alert);
    }
}

/**
 * Thread de surveillance des cameras
 */
void* scan(void*) {
    myMonit.metScan("/home/pi/Surveillance", "/home/pi/Images"); //Contient une boucle infinie
    //Pas de '/' de fin dans les noms de repertoire
    pthread_exit(NULL);
}

/**
 * Thread de surveillance de reception de SMS
 */
void* appel(void*) {
    maSim.recepSMS();
    pthread_exit(0);
}

/**
 * Thread de surveillance pour l'emission de SMS ou MMS
 */
void* sendXms(void*) {
    maSim.SendXMS(); //contient boucle infinie
    //pthread_exit(0);
}

/**
 * Thread de surveillance de coupure d'alim
 */
void* defAlim(void*) {
    int group = 1;
    stXm stX;

    if (wiringPiSetup() == -1) {
        printf("Erreur wiring PI");
        exit(0);
    }

    pinMode(3, INPUT);
    for (;;) {
        /*printf("%d", digitalRead(3)); delay(5);*/
        if (digitalRead(3) == 1 && b == 1) {
            delay(2000);
            dataBase.retour();
            string texto = "Retour du courant. ";
            texto += dateL();
            texto += '\0';
            //On diffuse le SMS en le mettant dans la list
            stX.type = 0; //sms
            stX.message = texto;
            stX.groupe = group;
            maSim.pushListXms(stX);
            b = 0;
        }

        if (digitalRead(3) == 0 && b == 0) {
            delay(2000);
            dataBase.coupure();
            string texto = "Coupure de courant. ";
            texto += dateL();
            texto += '\0';
            stX.type = 0; //sms
            stX.message = texto;
            stX.groupe = group;
            maSim.pushListXms(stX);
            b = 1;
        }
    }
    pthread_exit(0);
}

/**
 * ***********************************************************
 * main
 */
int main() {
    int nId, af = 0;
    int PIN = 2;
    int ferr, flog;
    int p1, p2, p3, p4;
    int clef3G = 0;
    mySwitch = new RCSwitch();
    RCSwitch::pft = alert433;
    tpsRebond = std::time(0);
    pthread_attr_t thread_attr;
    pthread_t recep;
    pthread_t survMonit;
    pthread_t alim;
    pthread_t sendXMS;


    //*** REDIRECTION des ports d'E/S ***
    ferr = open("/home/pi/domot.err", O_CREAT | O_APPEND | O_WRONLY | O_NONBLOCK);
    close(2); //On ferme la sortie d'erreur (stderr)
    dup(ferr); //pour la rediriger sur ce fichier

    flog = open("/home/pi/domot.log", O_CREAT | O_APPEND | O_WRONLY | O_NONBLOCK);
    close(1); //On ferme la sortie standard
    dup(flog); //pour la rediriger sur ce fichier

    if (pthread_attr_init(&thread_attr) != 0) {
        fprintf(stderr, "pthread_attr_init error");
        exit(1);
    }
    if (pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED) != 0) {
        fprintf(stderr, "pthread_attr_setdetachstate error");
        exit(1);
    }

    wiringPiSetup();
    //dataBase.updatestate(1);
    mySwitch->enableReceive(PIN); // Receiver on inerrupt 0 => that is pin #2

    //printf("Entrez le numero du port COM utilisé : ");
    //scanf("%d", &nId);
    printf("Version : 11/04/2019\n");
    printf("\nATTENTION lancer en sudo a cause du ping !\n");
    printf("On attend 6s le demarrage des services ...\n\n");
    sleep(6);

    maSim.setAdBDD(&dataBase);
    maSim.setAdMutex(&exMut);
    myMonit.setAdBdd(&dataBase);
    myMonit.setAdSim(&maSim);
    myMonit.effaceRepDeb("/home/pi/Surveillance");
    sleep(1);

    //Ouverture du ou des ports serie
    nId = 0;
    string np = to_string(nId);
    ttyPort1 = "/dev/ttyUSB" + np;
    nId = 2;
    string np2 = to_string(nId);
    ttyPort2 = "/dev/ttyUSB" + np2;
    maSim.setNomPort(ttyPort1, ttyPort2);
    maSim.ouvertureSerie(ttyPort1);
    if(dataBase.getcle3G() == 1)
        maSim.ouvertureSerie2(ttyPort2);
    sleep(1);

    //pthread_mutex_init(&exMut, NULL);
    exMut = PTHREAD_MUTEX_INITIALIZER;

    printf("Lancement threads\n");
    p2 = pthread_create(&survMonit, NULL, scan, NULL);
    p3 = pthread_create(&sendXMS, NULL, sendXms, NULL);
    //p4 = pthread_create(&alim, NULL, defAlim, NULL);
sleep(1);
    p1 = pthread_create(&recep, NULL, appel, NULL);
    if (p1 || p2 || p3)
        fprintf(stderr, "%s", strerror(p3));

    printf("Boucle infinie, animée /5mn\n");
    while (1) {
        // Animation
        if (af++ == 300) {
            printf(".");
            fflush(stdout);
            af = 0;
        }
        etat = dataBase.getstate();
        sleep(1);
    }

    //pthread_join(recep, NULL);
    //pthread_join(alim, NULL);
    //pthread_join(sendXMS, NULL);
    //pthread_join(survMonit, NULL);
    return 0;
}

