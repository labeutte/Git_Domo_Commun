/* 
 * File:   monitFTP.h
 */
#ifndef MONITFTP_H
#define MONITFTP_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/inotify.h>
#include <sys/select.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>
#include <string>
#include <dirent.h>
#include <vector>
#include "accesBDD.h"
#include "sim.h"

using namespace std;

class monitFTP {
    std::vector<std::string> adetruire;
    char repOrigine[512];
    char repDestination[512];
    string posGeo;
    string nomCam;
    std::time_t tpsMms;
    SIM* maSim;
    accesBDD* databdd;

public:
    monitFTP();
    virtual ~monitFTP();
    void info(char*);
    string dateL();
    void metScan(string, string);
    void traitFic(char*, char*);
    void traitRep(char*);
    int copier_fichier(char const *, char const *);
    void effaceRep();
    void effaceRepDeb(const char*);
    void setAdSim(SIM*);
    void setAdBdd(accesBDD*);
    //string getCheminMonit();
};

#endif /* MONITFTP_H */

