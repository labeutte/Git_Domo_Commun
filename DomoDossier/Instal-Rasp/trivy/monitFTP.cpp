/* 
 * File:   monitFTP.cpp
 */
#include "monitFTP.h"

monitFTP::monitFTP() {
    posGeo = "";
    tpsMms = 0;
}

monitFTP::~monitFTP() {
}

/**
 * 
 * @param ads
 */
void monitFTP::setAdSim(SIM*ads) {
    maSim = ads;
}

/**
 * 
 * @param adb
 */
void monitFTP::setAdBdd(accesBDD* adb) {
    databdd = adb;
}

/**
 * Information sur le type d'evenement declencheur
 * @param inf
 */
void monitFTP::info(char *inf) {
    string chemIm;
    stXm stX;
    int gr;
    //printf("info: %s\n", inf);
    string act = "AlerteCam : ";
    act += posGeo;
    //act += " ";
    //act += dateL();
    act += " ->";
    act += string(inf);
    gr = 1;
    chemIm = string(repDestination);
    chemIm += "/";
    chemIm += string(inf);
    databdd->putLastImg(string(inf));

    //On diffuse le SMS en le mettant dans la list
    stX.type = 0; //sms
    stX.message = act;
    stX.groupe = gr;
    maSim->pushListXms(stX);

    //On diffuse le MMS en le mettant dans la list
    stX.type = 1; //MMS
    stX.message = string(inf);
    stX.groupe = gr;
    stX.nomIm = string(inf);
    stX.chemIm = chemIm;
    maSim->pushListXms(stX);
}

/**
 * 
 * @param source
 * @param destination
 * @return 
 */
int monitFTP::copier_fichier(char const * const source, char const * const destination) {
    string cmd;
    cmd = "mv " + string(source) + "  " + string(destination);
    //printf("cmd %s\n",cmd.c_str());
    system(cmd.c_str());
    remove(source);
    return 0;
}

/**
 * 
 * @param repT
 */
void monitFTP::traitRep(char* repT) {
    DIR* rt;
    string pG = "";

    rt = opendir(repT);
    if (rt != NULL) {
        struct dirent* ent;
        usleep(500 * 1000);
        while ((ent = readdir(rt)) != NULL) {
            if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..")) {
                if (ent->d_type == 4) {
                    //printf("sousRep : %s\n", ent->d_name);
                    char repTemp[512];
                    strcpy(repTemp, repT);
                    strcat(repTemp, "/");
                    strcat(repTemp, ent->d_name);
                    adetruire.push_back(string(repTemp));
                    traitRep(repTemp);
                }
                if (ent->d_type == 8) {
                    //printf("sousFichier : %s\n", ent->d_name);
                    char repTemp[512];
                    strcpy(repTemp, repT);
                    strcat(repTemp, "/");
                    strcat(repTemp, ent->d_name);
                    traitFic(repTemp, ent->d_name);
                }

            }
        }
    }
}

/**
 * Donne un nom Ã  l'image avec la date
 */
string nomImageDate() {
    const char* nomMois[] = {"janv", "fev", "mar", "avr", "mai", "juin", "juil", "aout", "sept", "oct", "nov", "dec"};

    char locTime[30];
    time_t TH;
    struct tm* t;
    TH = time(NULL);
    t = localtime(&TH);
    sprintf(locTime, "%02u%s%04u_%02u:%02u:%02u.jpg", t->tm_mday, nomMois[t->tm_mon], 1900 + t->tm_year, t->tm_hour, t->tm_min, t->tm_sec);
    return (string(locTime));
}

/**
 * Copie l'image dans le rep de destination si on est en
 * mode "Marche"
 * chem : nom complet (image comprise)
 * nomFic : nom dse l'image 
 */
void monitFTP::traitFic(char* chem, char* nomFic) {
    int cr, etatM;
    char dest[512];
    char nouveauNom[70];
    strcpy(dest, repDestination);
    strcat(dest, "/");
    strcpy(nouveauNom, nomCam.c_str());
    strcat(nouveauNom, "-");
    strcat(nouveauNom, nomImageDate().c_str());
    strcat(dest, nouveauNom);
    etatM = databdd->getstate();
    nomCam = "";
    if (etatM) {
        if (std::time(0) - tpsMms > 5) { // Au moins 5s entre 2 envois
            tpsMms = std::time(0); // a cause des fichiers multiples
            //printf("\nFichier = %s\n", nomFic);
            cr = copier_fichier(chem, dest);
            info(nouveauNom);
        }
    } else {
        remove(chem);
    }
    posGeo = "";
    effaceRep();
}

/**
 * efface les sous-repertoires de celui qui est Ã  monitorer
 */
void monitFTP::effaceRep() {
    //printf("taille: %d\n", adetruire.size());
    for (int i = adetruire.size(); i > 0; i--) {
        //printf("destruction: %s\n", adetruire[i - 1].c_str());
        rmdir(adetruire[i - 1].c_str());
        adetruire.pop_back();
    }
}

/**
 * 
 * @param repT
 */
void monitFTP::effaceRepDeb(const char* repT) {
    DIR* rt;
    string pG = "";

    rt = opendir(repT);
    if (rt != NULL) {
        struct dirent* ent;
        usleep(500 * 1000);
        while ((ent = readdir(rt)) != NULL) {
            if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..")) {
                if (ent->d_type == 4) {
                    //printf("sousRep : %s\n", ent->d_name);
                    char repTemp[512];
                    strcpy(repTemp, repT);
                    strcat(repTemp, "/");
                    strcat(repTemp, ent->d_name);
                    adetruire.push_back(string(repTemp));
                    effaceRepDeb(repTemp);
                }
                if (ent->d_type == 8) {
                    //printf("sousFichier : %s\n", ent->d_name);
                    char repTemp[512];
                    strcpy(repTemp, "sudo rm ");
                    strcat(repTemp, repT);
                    strcat(repTemp, "/*");
                    //fprintf(stderr, "effaceRepDeb : %s\n", repTemp);
                    system(repTemp);
                }
                effaceRep();
            }
        }
    }
}

/**
 * Thread de monitoring d'un repertoire
 * @param path = chemin a monitorer
 */
void monitFTP::metScan(string path, string destin) {
    int fd, wd, rwd;
    fd_set fds;
    char buffer[512];
    struct inotify_event *event;
    DIR* rac;
    char aDetruire[512];
    string pG = "";
    string dt;

    strcpy(repOrigine, path.c_str());
    strcpy(repDestination, destin.c_str());
    dt = dateL();
    printf("%s-\033[32mMonitoring : \033[00m \033[31m%s\033[00m\n", dt.c_str(), repOrigine);
    fd = inotify_init();
    if (fd < 0) {
        perror("inotify Initialisation : ");
        exit(2);
    }
    // Surveillance du fichier/rÃ©pertoire passÃ© en paramÃ¨tre
    wd = inotify_add_watch(fd, repOrigine, IN_CREATE);
    if (wd < 0) {
        perror("inotify Watch : ");
    }
    /////
    while (1) {
        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        if (select(fd + 1, &fds, NULL, NULL, 0) <= 0) {
            continue;
        }
        if (read(fd, buffer, sizeof (buffer)) < 0)
            perror("err read : ");
        event = (struct inotify_event *) buffer;
        dt = dateL();
        //printf("\n%s- Creation : %s\n", dt.c_str(), event->name);
        rac = opendir((const char*) repOrigine);
        if (rac != NULL) {
            struct dirent* ent;
            int b = 1;
            while ((ent = readdir(rac)) != NULL) {
                if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..")) {
                    //printf("->%d : %s, type : %d\n", b++, ent->d_name, ent->d_type);
                    if (ent->d_type == 4) {
                        //printf("Repertoire : %s\n", ent->d_name);
                        nomCam = (string) (ent->d_name);
                        strcpy(aDetruire, ent->d_name);
                        char repTemp[512];
                        strcpy(repTemp, repOrigine);
                        strcat(repTemp, "/");
                        strcat(repTemp, ent->d_name);
                        adetruire.push_back(string(repTemp));
                        pG = databdd->getcamGeo(string(ent->d_name));
                        if (pG != "inconnue") {
                            posGeo = pG;
                        }
                        traitRep(repTemp);
                        rmdir(repTemp);
                    }
                    if (ent->d_type == 8) {
                        //printf("Fichier sous la racine: %s\n", ent->d_name);
                        char repTemp[512];
                        strcpy(repTemp, repOrigine);
                        strcat(repTemp, "/");
                        strcat(repTemp, ent->d_name);
                        traitFic(repTemp, ent->d_name);
                    }
                }
            }
            //closedir(rep);
        }
    }
    pthread_exit(0);
}

/**
 * date au format franÃ§ais
 */
string monitFTP::dateL() {
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

