#!/bin/bash
# install-Appli.sh
# version du 18/04/2019
#
# cd /home/pi/Instal-Rasp
dos2unix Scripts/*
dos2unix trivy/*
dos2unix Application-www/*
#
echo Copie des fichiers de l'application ...
#
#l'application
sudo mkdir /home/pi/script
sudo cp Scripts/*  /home/pi/script/
sudo chown pi.pi /home/pi/script
sudo chmod a+x /home/pi/script/*
cd /home/pi/script
dos2unix *
cd /home/pi
#
sudo mkdir /home/pi/Surveillance
sudo chown pi.pi /home/pi/Surveillance
sudo chmod a+x /home/pi/Surveillance
sudo mkdir /home/pi/Images
sudo chown pi.pi /home/pi/Images
#
sudo mkdir /home/pi/trivy
sudo chown pi.pi /home/pi/trivy
#
sudo cp ../trivy/* /home/pi/trivy/
sudo chown pi.pi -R /home/pi/trivy
dos2unix /home/pi/trivy/*
sudo chmod a+x /home/pi/trivy/appli

sudo hwclock -D -r

echo Fichiers copiés
echo Pensez à modifier cron : sudo crontab -e 
echo --- REBOOTEZ !
echo et faites :sudo hwclock -D -r
echo  pour vérifier heure
