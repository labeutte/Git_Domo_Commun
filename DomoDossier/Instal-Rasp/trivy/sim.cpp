/* 
 * File:   SIM.cpp
 * Author: aucaigne
 */
#include <algorithm> // pour std::transform
#include "sim.h"

#define couleur(param) fprintf(stderr,"\033[%sm",param)

SIM::SIM() {
    etat = 0;
    tps = 0;
    etatReseau = true;
    strcpy(my_phone_number, "+33769101655");
    strcpy(mmsAPN, "mmsfree");
    strcpy(mmsCentre, "mms.free.fr"); //mms.free.fr";
    strcpy(mmsCentreH, "http://212.27.40.225"); //mms.free.fr";
    strcpy(mmsCentreIP, "212.27.40.225");
    strcpy(mmsProxy, "212.27.40.225");
    mmsPort = 80;
    nomPortSerie = "";
    numReqSms = "+33651980787"; //valeur par défaut au démarage
    memset(imageMMS, '\0', 307999);
    memset(textMMS, '\0', 15359);
    ipInterrupt1 = "192.168.3.41"; // IP de l'ESP pour VMC
}

SIM::~SIM() {
}

/**
 * @return 
 */
string SIM::getNumReqSms() {
    return numReqSms;
}

/**
 * 
 * @param snp
 */
void SIM::setNomPort(string snp, string snp2) {
    nomPortSerie = snp;
    nomPortSerie2 = snp2;
}

/**
 * 
 * @param ad
 */
void SIM::setAdBDD(accesBDD* ad) {
    adbdd = ad;
    reseau.setAdBDD(ad);
}

/**
 * 
 * @param exmut
 */
void SIM::setAdMutex(pthread_mutex_t* exmut) {
    myMutex = exmut;
}

/**
 *
 */
string SIM::dateL() {
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
 * @param lePort
 * @return 
 */
int SIM::ouvertureSerie(string lePort) {
    string niveauGSM, seuil;
    string etatM = "";
    string nivo = "req CSQ non trouvée";
    string leSite = "";
    int nivoEnt = -1;
    stXm stX;
    fdPort = maCom.openTTY(lePort.c_str());
    dt = dateL();
    printf("\n%s - %s Ouvert= %d\n", dt.c_str(), lePort.c_str(), fdPort);
    maCom.sendAT("AT+IFC=0,0;+IPR=0;&W\r", "IFC", 10000); // Pas de poignee de main et vitesse auto.
    //maCom.sendAT("AT+IFC=1,1;+IPR=0;&W\r", "IFC", 3000); // Xon/XOFF
    maCom.sendAT("AT+CMEE=2\r", "OK", 10000); //Active code d'erreur
    //maCom.sendAT("AT+CPIN=\"1234\"\r", "OK", 500);
    ////maCom.sendAT("AT+CREG?\r", "OK", 800); //liste des r�seaux support�s
    /*
    2eme parametre recu :
    Possible values for access technology are,
    0 GSM
    1 GSM Compact
    2 UTRAN
    3 GSM w/EGPRS
    4 UTRAN w/HSDPA
    5 UTRAN w/HSUPA
    6 UTRAN w/HSDPA and HSUPA
    7 E-UTRAN
     */
    niveauGSM = maCom.sendAT("AT+CSQ\r", "OK", 10000); // Niveau de reseau
    sleep(1);
    //si <10 Mauvais
    //si >10 OK
    //si >15 Bon
    //si >20 Excellent    

    //On diffuse le SMS en le mettant dans la list
    niveauGSM = niveauGSM.substr(7);
    int foundCsq = niveauGSM.find("+csq");
    printf("Niveau de GSM (< 10 Mauvais, >15 Bon) = ");
    if (foundCsq > 1 && foundCsq < 255) {
        nivo = niveauGSM.substr(foundCsq, 10);
        seuil = niveauGSM.substr(foundCsq + 6, 4);
        int virg = seuil.find(",");
        string vv = seuil.substr(0, virg);
        nivoEnt = stoi(vv);
        printf(" %s, donc %d\n", seuil.c_str(), nivoEnt);
    } else {
        printf("Mauvais CSQ : %s, donc %d\n", seuil.c_str(), nivoEnt);
    }
    /*** Traitement si niveau csq < 10 ***/
    /****On ne fait pas ce test pour la cle 3G
    if (nivoEnt < 10) {
        etatReseau = false; //On est en mode dégradé sans SMS ni MMS
        printf("==> Mode degrade PAS de MMS\n");
    }
     */
    leSite = adbdd->getNomSite();
    etat = adbdd->getstate();
    if (etat)
        etatM = ", " + leSite + ": En marche";
    else
        etatM = ", " + leSite + ": A l'arret";

    stX.type = 0; //sms
    stX.message = nivo + etatM;
    stX.groupe = 1;
    pushListXms(stX);
    return fdPort;
}

/**
 * @param lePort
 * @return 
 */
int SIM::ouvertureSerie2(string lePort) {
    stXm stX;
    fdPort2 = maCom2.openTTY(lePort.c_str());
    printf("%s - %s Ouvert2= %d\n", dt.c_str(), lePort.c_str(), fdPort2);
    maCom2.sendAT("AT+IFC=0,0;+IPR=0;&W\r", "IFC", 10000); // Pas de poignee de main et vitesse auto.
    //maCom.sendAT("AT+IFC=1,1;+IPR=0;&W\r", "IFC", 3000); // Xon/XOFF
    maCom2.sendAT("AT+CMEE=2\r", "OK", 10000); //Active code d'erreur
    return fdPort2;
}

/**
 * 
 * @param numero string numéro GSM reception
 * @param message contenu du sms
 * @return 1
 */
int SIM::envSMS(string numero, string message) {
    string answer;
    char aux_string[350];
    char numR[25];
    //cout << "SMS demande SC" << endl;
    pthread_mutex_lock(myMutex);

    memset(aux_string, '\0', 118);
    maCom.sendAT("AT+CMGF=1\r", "OK", 10000); // Activation du mode texte pour les SMS.
    strcpy(numR, numero.c_str());
    sprintf(aux_string, "AT+CMGS=\"%s\"\r", numR);
    answer = maCom.sendAT(aux_string, ">", 10000); // Envoi du numero de tel au module GSM.
    if (answer != "") {
        memset(textSms, '\0', 143);
        // On insere le corps du message.
        strcpy(textSms, message.c_str());
        int lgSms = strlen(textSms);
        textSms[lgSms] = 0x1A; //OBLIGATOIRE !!!
        textSms[lgSms + 1] = '\0';
        usleep(5000);
        maCom.sendAT(textSms, textSms, 10000);
        usleep(lgSms * 1600);
    } else {
        fprintf(stderr, "Erreur sur CMGS (emiss message) !");
    }
    sleep(2);
    //cout << "SMS va sortir SC" << endl;
    pthread_mutex_unlock(myMutex);
    dt = dateL();
    printf("\n%s - SMS envoye : %s : %s\n", dt.c_str(), numero.c_str(), message.c_str());
    return (1);
}

void display_sched_attr(int policy, struct sched_param *param) {
    fprintf(stderr, "    policy=%s, priority=%d\n",
            (policy == SCHED_FIFO) ? "SCHED_FIFO" :
            (policy == SCHED_RR) ? "SCHED_RR" :
            (policy == SCHED_OTHER) ? "SCHED_OTHER" :
            "???",
            param->sched_priority);
}

/**
 * 
 * @param numero du destinataire
 * @param txMMS message du mms
 * @param nomImage nom de l'image
 * @param cheminImage chemin d'acces à l'image
 * @return 1
 */
int SIM::envMMS(string numero, string txMMS, string nomImage, string cheminImage) {
    FILE *fd;
    int ix = 0;
    string scr;
    // On place la priorité du thread en RR 80 (très élevée)
    //struct sched_param param;
    //int policy, s;
    //s = pthread_getschedparam(pthread_self(), &policy, &param);
    //display_sched_attr(policy, &param);
    //policy = SCHED_RR; //SCHED_FIFO;
    //param.sched_priority = 80;
    //printf("fifoM %d\n", sched_get_priority_max(SCHED_FIFO)); 	//99
    //printf("fifom %d\n", sched_get_priority_min(SCHED_FIFO)); 	//1
    //printf("rr %d\n", sched_get_priority_max(SCHED_RR));		//99
    //printf("other %d\n", sched_get_priority_max(SCHED_OTHER));	//0
    //s = pthread_setschedparam(pthread_self(), policy, &param);
    //if (s != 0)
    //    perror("pthread_setschedparam");
    //s = pthread_getschedparam(pthread_self(), &policy, &param);
    //display_sched_attr(policy, &param);
    //************************/

    memset(imageMMS, '\0', 307999);
    memset(textMMS, '\0', 15359);
    dt = dateL();
    printf("\n%s - MMS : %s : %s\n", dt.c_str(), numero.c_str(), txMMS.c_str());

    //puts("Chargement de l'image ...");
    fd = fopen(cheminImage.c_str(), "rb");

    while (!feof(fd)) {
        fread(&imageMMS[ix++], 1, 1, fd);
        //fprintf(stderr,"%x ",image[ix-1]);
    }
    //fprintf(stderr,"\nix=%d car =%x\n",ix, image[ix-2]);
    //    image[ix-1]=0x1A;
    imageMMS[ix - 1] = '\r';
    imageMMS[ix] = '\0';
    int lgIm = ix; //Le dernier caractere est le D9 de fin de JPG
    if ((lgIm) >= 307200)
        fprintf(stderr, "ERREUR, l'image est trop grosse !");
    fclose(fd);
    //puts("---> fin de chargement\n");

    //cout << "MMS demande SC" << endl;
    pthread_mutex_lock(myMutex);

    //puts("PREPA Reseau\n");
    maCom.sendAT("AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r", "OK", 10000); //GPRS possible
    sprintf(aux_string, "AT+SAPBR=3,1,\"APN\",\"%s\"\r", mmsAPN); //APN );
    maCom.sendAT(aux_string, "OK", 10000);
    maCom.sendAT("AT+SAPBR=1,1\r", "OK", 10000);
    maCom.sendAT("AT+SAPBR=2,1\r", "OK", 10000);

    maCom.sendAT("AT+CMMSINIT\r", "OK", 10000);
    //PROTO=Proxy et free n'en utilise pas mais ...
    sprintf(aux_string, "AT+CMMSPROTO=\"%s\",%d\r", mmsProxy, mmsPort);
    maCom.sendAT(aux_string, "OK", 10000);

    sprintf(aux_string, "AT+CMMSCURL=\"%s\"\r", mmsCentreIP); //sans le http:// ou mmsCentre
    maCom.sendAT(aux_string, "OK", 10000);
    maCom.sendAT("AT+CMMSCID=1\r", "OK", 3000); // celui du SAPBR !
    //maCom.sendAT("AT+CMMSSENDCFG=6,3,0,0,2,4\r", "OK", 3000); //CMMSSENDCFG: <valid>,<pri>,<sendrep>,<readrep>,<visible>,<class>,<subctrl>,<notifyskip>
    maCom.sendAT("AT+CMMSSENDCFG=1,1,0,0,1,4,2,0\r", "OK", 3000); //CMMSSENDCFG: <valid 12h>,<pri normal>,<sendrep Pas rappot>,<readrep Pas de rapport>,<visible Oui>,<class 4 Not Set>,<subctrl 2=english>,<notifyskipHTTP 0=wait, 1=skip>
    /////maCom.sendAT("AT+CMMSSENDCFG?\r", "OK", 3000);

    maCom.sendAT("AT+CMMSEDIT=1\r", "OK", 10000);

    //l'image
    sprintf(aux_string, "AT+CMMSDOWN=\"PIC\",%d,50000,\"%s\"\r", lgIm, nomImage.c_str());
    maCom.sendAT(aux_string, "OK", 50000);
    //puts("Depot de l'image du MMS ...");
    maCom.writeTTY((char*) imageMMS, lgIm);
    usleep(1000 * 1000);

    //le TEXTE
    strcpy(textMMS, txMMS.c_str());
    int lgMms = strlen(textMMS);
    sprintf(aux_string, "AT+CMMSDOWN=\"TEXT\",%d,40000,\"%s\"\r", lgMms, textMMS);
    maCom.sendAT(aux_string, "OK", 40000);
    //puts("Depot du texte du MMS ...");
    maCom.writeTTY((char*) textMMS, lgMms + 1);
    usleep(300 * 1000);

    ////maCom.sendAT("AT+CMMSSTATUS?\r", "OK", 3000);
    sprintf(aux_string, "AT+CMMSRECP=\"%s\"\r", numero.c_str());
    maCom.sendAT(aux_string, "OK", 20000);
    scr = maCom.sendAT("AT+CMMSVIEW\r", "OK", 20000);
    //cout << "view " << scr << endl;
    scr = maCom.sendAT("AT+CMMSSEND\r", "OK", 50000);
    //cout << "send " << scr << endl;
    // A raison de 1150 caracteres par seconde: 
    usleep(lgIm * 1000);
    //    sleep(16);
    for (int k = 1; k < 2; k++) {
        sprintf(aux_string, "AT+CMMSDELFILE=\"%d\"\r", k);
        scr = maCom.sendAT(aux_string, "OK", 10000);
    }
    printf("=> fermeture MMS\n");
    scr = maCom.sendAT("AT+CMMSEDIT=0\r", "OK", 10000);
    //cout << "edit " << scr << endl;
    scr = maCom.sendAT("AT+CMMSTERM\r", "OK", 10000);
    sleep(3);
    dt = dateL();
    printf("\n%s - MMS envoye: %s : %s\n", dt.c_str(), numero.c_str(), txMMS.c_str());

    //cout << "MMS va sortir SC" << endl;
    pthread_mutex_unlock(myMutex);

    // On remet la priorité normale
    //policy = SCHED_OTHER; //SCHED_FIFO;
    //param.sched_priority = 0;
    //s = pthread_setschedparam(pthread_self(), policy, &param);
    //if (s != 0)
    //    perror("pthread_setschedparam");
    return (1);
}

/**
 * 
 * @param messAdif
 * @param gr
 */
void SIM::diffSMS(string messAdif, string gr) {
    int i = 0, nbN, cr;
    string token;
    string sgr;
    sgr = adbdd->getnum(gr); // retourne les numeros du groupe "gr"
    // dans une string séparés par un tiret "-"

    //cout<<"liste: "<<sgr<<endl;
    istringstream iss(sgr);
    while (getline(iss, token, '-')) // sépare les numéros et les placent dans un tableau
    {
        contact[i] = token;
        //cout << contact[i] << endl;
        i++;
    }
    nbN = i;
    for (i = 0; i <= (nbN - 1); i++) // faire un envoi pour chaque contact trouvé
    {
        cr = envSMS(contact[i], messAdif);
        //cout << "Diffusion, SMS envoye a : " << contact[i] << " : " << messAdif << endl;
    }
}

/**
 * Diffusion de MMS
 * @param messAdif
 * @param gr
 */
void SIM::envImgFtp(string cheminImage) {
    // On envoi l'image sur le serveur FTP public s'il y a du réseau
    reseau.putFTP(cheminImage);
}

/**
 * Diffusion de MMS
 * @param messAdif
 * @param gr
 */
void SIM::diffMMS(string messAdif, string gr, string nomImage, string cheminImage) {
    compress *comp = new compress();
    string reduite = "/home/pi/Images/0A-reduite.jpg";
    string imgTmp = "/home/pi/Images/0B-tempo.jpg";
    int i = 0, nbN, cr;
    string token;
    string sgr;

    sgr = adbdd->getnum(gr); // retourne les numeros du groupe "gr"
    // dans une string séparés par un tiret "-"

    //cout<<"liste: "<<sgr<<endl;
    istringstream iss(sgr);
    while (getline(iss, token, '-')) // sépare les numéros et les placent dans un tableau
    {
        contact[i] = token;
        //cout << contact[i] << endl;
        i++;
    }
    nbN = i;
    //preparation d l'image envoyee (reduction)

    cv::Mat src = cv::imread(cheminImage.c_str());
    cv::Mat dest(600, 400, CV_8UC2); //, cv::Scalar(0, 0, 0));
    //dest = src.clone();
    cv::Size size(600, 400);
    cv::resize(src, dest, size, 1, 1, cv::INTER_LINEAR);
    cv::imwrite(imgTmp.c_str(), dest);

    comp->compression(imgTmp, reduite, 15); //compression 20%

    //cout<<"Emission im"<<endl;
    //Envoi de l'image réduite
    for (int i = 0; i <= (nbN - 1); i++) // faire un envoi pour chaque contact trouvé
    {
        //*************
        //ICI on envoi pas de MMS
        //Ca ne marche pas avec cette carte ...
        ////cr = envMMS(contact[i], messAdif, nomImage, reduite);
        sleep(2);
    }
}

/**
 * 
 * @return le message reçu
 */
void SIM::recepSMS() {
    fd_set rfds;
    string repAT, numE, minus, SMS_;
    size_t found = 0, foundNum = 0, foundA = 0;
    int debN, retval, nbrec, port_recep;
    bool trouv = false, clef3G = false;
    static unsigned int np = 0;

    if (adbdd->getcle3G() == 1) {
        clef3G = true;
        port_recep = fdPort2;
    } else {
        clef3G = false;
        port_recep = fdPort;
    }

    while (1) {
        sleep(3);
        minus = "";
        repAT = "";
        SMS_ = "";

        if (clef3G == false) {
            //cout << "\nRecep demande SC" << endl;
            pthread_mutex_lock(myMutex);
        }

        FD_ZERO(&rfds);
        FD_SET(fdPort, &rfds);
        tv.tv_sec = 2; //attente maxi de 2s
        tv.tv_usec = 0;
        do {
            retval = select(fdPort + 1, &rfds, NULL, NULL, &tv);
        } while (retval < 0);
        //cout << "\nretval=" << retval << "\t  ISSET=" << FD_ISSET(fdPort, &rfds) << endl;
        if ((retval > 0 && FD_ISSET(fdPort, &rfds)) && etatReseau) {
            //il y a des données dispo
            //puts("recep : Des données");
            if (clef3G == false) {
                maCom.sendAT("AT+CMGF=1\r", "OK", 10000); //mode SMS
                usleep(500 * 1000);
                repAT = maCom.sendAT("AT+CMGL=\"REC UNREAD\"\r", "OK", 10000); //Affiche messages non lus
                //maCom.sendAT("AT+CMGL=\"ALL\"\r", "OK", 5000); //Affiche tous les messages
            } else {
                maCom2.sendAT("AT+CMGF=1\r", "OK", 10000); //mode SMS
                usleep(500 * 1000);
                repAT = maCom2.sendAT("AT+CMGL=\"REC UNREAD\"\r", "OK", 10000); //Affiche messages non lus
            }
            usleep(700 * 1000);
            //cout << "repAT=" << repAT << "<=" << endl;
            minus = repAT;
            nbrec = minus.length();
            std::transform(minus.begin(), minus.end(), minus.begin(), ::tolower);
            found = minus.find("unread");
            if (nbrec > 28 && ((int) found > 2)&& ((int) found < 500)) { //si au moins 1 sms recu
                if (clef3G == false) {
                    maCom.sendAT("AT+CMGD=1,1\r", "OK", 5000); //supprime SMS lus
                } else {
                    maCom2.sendAT("AT+CMGD=1,1\r", "OK", 5000); //supprime SMS lus
                }
                usleep(500 * 1000);
                if (!clef3G) {
                    //cout << "Recep va sortir SC avec message" << endl;
                    pthread_mutex_unlock(myMutex);
                }
                int y = 0;
                trouv = false;
                //cout<<"repAT="<<repAT<<"<|"<<endl;

                stringstream ss(repAT);
                string sousChaine;
                int k = 0;
                bool trouv = false;
                while (getline(ss, sousChaine, '\n')) {
                    //cout<<k++<<">"<<sousChaine<<endl;
                    //on extrait le numéro du demandeur
                    foundNum = sousChaine.find("+33");
                    if (foundNum > 10 && foundNum < 255) { // on a trouvé
                        trouv = true;
                        numE = sousChaine.substr(foundNum, 12);
                    }
                    for (int u = 0; u < (int) sousChaine.length(); u++) {
                        if (sousChaine[u] == 0x40) { // symbole @
                            SMS_ = sousChaine;
                        }
                    }
                }
                if (trouv) {
                    //cout << "num=" << numE << endl;
                    //cout << "SMS=" << SMS_ << endl;
                    numReqSms = numE;
                    traitRecepSms(SMS_);
                } else {
                    traitRecepSms("0000@mauvais");
                }
            }
            if (clef3G == false) {
                //cout << "Recep va sortir SC rien lu" << endl;
                pthread_mutex_unlock(myMutex);
            }
        } else {
            if (clef3G == false) {
                //cout << "Recep va sortir SC sans message" << endl;
                pthread_mutex_unlock(myMutex);
            }
        }
        //cout << "> S Recep " << np++ << endl;
    }
}

/**
 * 
 * @param ordre
 */
void SIM::traitRecepSms(string ordre) {
    bool autoris;
    stXm stX;
    int cr;
    char commande[50];
    size_t p = ordre.find("@");
    float teta = 0;
    string act = "";
    ostringstream os;
    string mdp = ordre.substr(0, p);
    string action = ordre.substr(p + 1, ordre.length());
    //cout << "mdp=" << mdp << "  action=" << action << endl;
    //cout << "action=" << action << endl;

    if (ordre.find("mauvais") > 0 && ordre.find("mauvais") < 8) {
        act = "Ordre non compris";
        stX.type = 2; //sms avec 1 seul destinat
        stX.message = act;
        stX.destin = numReqSms;
        ////pushListXms(stX);
    } else {
        autoris = adbdd->testpwdSMS(mdp);
        if (autoris) {
            std::transform(ordre.begin(), ordre.end(), ordre.begin(), ::tolower);
            etat = adbdd->getstate();
            //cout << "etat:" << etat << "  autoris=" << autoris << endl;
            if (ordre.find("arret") > 0 && ordre.find("arret") < 8) {
                dt = dateL();
                printf("\n%s - Arret demande\n", dt.c_str());
                adbdd->updatestate(0);
                act = "Arret du Systeme";
                stX.type = 2; //sms avec 1 seul destinat
                stX.message = act;
                stX.destin = numReqSms;
                pushListXms(stX);
            } else if (ordre.find("marche") && ordre.find("marche") < 8) {
                dt = dateL();
                printf("\n%s - Marche demandee\n", dt.c_str());
                adbdd->updatestate(1);
                act = "Mise en marche";
                stX.type = 2; //sms avec 1 seul destinat
                stX.message = act;
                stX.destin = numReqSms;
                pushListXms(stX);
            } else if (ordre.find("statut") && ordre.find("statut") < 8) {
                if (etat == 1)
                    act = "Systeme en marche";
                else {
                    act = "Systeme a l'arret";
                }
                stX.type = 2; //sms avec 1 seul destinat
                stX.message = act;
                stX.destin = numReqSms;
                pushListXms(stX);
            } else if (ordre.find("vmc0") && ordre.find("vmc0") < 8) {
                if (reseau.ping(ipInterrupt1.c_str())) {
                    strcpy(commande, "curl http://192.168.3.41/gpio/0 &");
                    system(commande);
                    act = "Arret VMC";
                } else
                    act = "Interrupt pas present";
                stX.type = 2; //sms avec 1 seul destinat
                stX.message = act;
                stX.destin = numReqSms;
                pushListXms(stX);
            } else if (ordre.find("vmc1") && ordre.find("vmc1") < 8) {
                if (reseau.ping(ipInterrupt1.c_str())) {
                    strcpy(commande, "curl http://192.168.3.41/gpio/1 &");
                    system(commande);
                    act = "Marche VMC";
                } else
                    act = "Interrupt pas present";
                stX.type = 2; //sms avec 1 seul destinat
                stX.message = act;
                stX.destin = numReqSms;
                pushListXms(stX);
            } else if (ordre.find("temp") && ordre.find("temp") < 8) {
                teta = adbdd->gettemp(21); // 1 seul capteur pour l'instant
                act = "Temperature ";
                os << teta;
                act += os.str();
                act += " degres";
                stX.type = 2; //sms avec 1 seul destinat
                stX.message = act;
                stX.destin = numReqSms;
                pushListXms(stX);
            } else if (ordre.find("photo") && ordre.find("photo") < 8) {
                string nIm = ordre.substr(10, 2);
                //cout<<"Image N "<<nIm<<endl;
                if (nIm != " ") {
                    string ficImg = adbdd->getLastImg(nIm);
                    //fprintf(stderr,"img= %s\n", ficImg.c_str());
                    string a_env = "/home/pi/Images/" + ficImg;
                    stX.type = 1; //MMS
                    stX.message = ficImg;
                    stX.groupe = 1;
                    stX.nomIm = ficImg;
                    stX.chemIm = a_env;
                    pushListXms(stX);
                } else {
                    stX.type = 2; //SMS avec 1 seul destinat
                    stX.message = "Pas d'image";
                    stX.destin = numReqSms;
                    pushListXms(stX);
                }
            } else if (ordre.find("reboot") && ordre.find("reboot") < 8) {
                act = "Reboot demande";
                stX.type = 2; //sms avec 1 seul destinat
                stX.message = act;
                stX.destin = numReqSms;
                pushListXms(stX);
                system("reboot");
            } else {
                cout << "Ordre Inconnu" << endl;
                /*** On fait rien a cause des pub recues 
                stX.type = 2; //sms avec 1 seul destinat
                stX.message = "Ordre inconnu";
                stX.destin = numReqSms;
                pushListXms(stX);
                 */
            }
        } else {
            stX.type = 2; //sms avec 1 seul destinat
            stX.message = "Mauvais mot de passe";
            stX.destin = numReqSms;
            pushListXms(stX);
        }
    }
}

void SIM::SendXMS() {
    stXm im;
    string dt;
    while (1) {
        if (!listXMS.empty()) {
            if (im.type == 0 || im.type == 1 || im.type == 2) {
                dt = dateL();
                im = listXMS.front();
                //printf("\n==> XMS");
                if (im.type == 0) { //SMS
                    //printf(" - SMS\n");
                    //cout << "Depile : " << im.message << endl;
                    listXMS.pop_front(); //On dépile
                    diffSMS(im.message, to_string(im.groupe));
                }
                if (im.type == 1) { //MMS 
                    if (std::time(0) - tps > 60) { // On ne peut envoyer un MMS que ttes les mn
                        //printf(" - MMS\n");
                        //cout << "DEpile : " << im.message << endl;
                        listXMS.pop_front(); //On défile
                        tps = std::time(0);
                        /////////
                        // PAS DE MMS SUR CETTE CONFIG
                        //diffMMS(im.message, to_string(im.groupe), im.nomIm, im.chemIm);
                        ////////////
                        envImgFtp(im.chemIm);
                    }
                }
                if (im.type == 2) { //SMS avec 1 seul destinat, réponse à requete
                    //printf(" - SMS de reponse\n");
                    //cout << "DEpile : " << im.message << endl;
                    listXMS.pop_front(); //On dépile
                    envSMS(im.destin, im.message);
                }
            }
        }
        sleep(1);
    }
}

void SIM::pushListXms(stXm sti) {
    etat = adbdd->getstate();
    if ((etat == 1 || sti.message == "Arret du Systeme" || sti.message == "Systeme a l'arret" || sti.message.find("A l'arret")) && etatReseau) {
        //cout<<"empile : "<<sti.message<<endl;
        listXMS.push_back(sti);
    }
}
