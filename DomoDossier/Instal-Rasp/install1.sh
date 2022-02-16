#!/bin/bash
# install1.sh
# version du 04/03/2019
#
echo Installation ...
echo APACHE
sudo apt-get install -y  apache2
sudo chown  pi.www-data  /var/www/html -R
sudo chmod 770  /var/www/html -R
#
echo PHP
sudo apt-get install -y  php
#
echo MYSQL
sudo apt-get install -y  mysql-client mysql-server php-mysql
sudo apt-get install -y  default-libmysqlclient-dev
sudo apt-get install -y  libmariadbclient-dev-compat
#
echo LIBCURL
sudo apt-get install -y  libcurl4-openssl-dev
#
echo PURE-FTP
sudo apt-get install pure-ftpd pure-ftpd-common
sudo groupadd ftpgroup
sudo useradd -g ftpgroup -d /dev/null -s /etc ftpuser
#
# echo MOTION
# sudo apt-get install -y  motion
#
echo WIFI
sudo apt-get install -y  dnsmasq hostapd
#
echo RTC
sudo apt-get install -y  python-smbus
sudo apt-get install -y  i2c-tools
#
echo NTP
sudo apt-get install -y  ntp
#
echo OPENCV
sudo apt-get install -y cmake gcc g++ libx11-dev libxt-dev libxext-dev libgraphicsmagick1-dev libcv-dev libhighgui-dev
#
echo DOS2UNIX
sudo apt-get install -y dos2unix
#
echo PHPMYADMIN
echo "Avant d'installer PHPMYADMIN tapez les comandes siuvantes :"
echo sudo mysql -u root
echo use mysql;
echo update user set plugin='' where User='root';
echo flush privileges;
echo exit;
echo "shell$ mysql --user=root mysql"
echo mysql> ....
echo CREATE USER 'gilles'@'localhost' IDENTIFIED BY 'gilles';
echo GRANT ALL PRIVILEGES ON *.* TO 'gilles'@'localhost' WITH GRANT OPTION;
echo CREATE USER 'gilles'@'%' IDENTIFIED BY 'gilles';
echo GRANT ALL PRIVILEGES ON *.* TO 'gilles'@'%' WITH GRANT OPTION;
echo CREATE USER 'admin'@'localhost' IDENTIFIED BY 'admin';
echo GRANT RELOAD,PROCESS ON *.* TO 'admin'@'localhost';
echo SET PASSWORD FOR root@'localhost'=PASSWORD('root');
echo CREATE database Surveillance;
echo " "
echo "Appuyer sur Entrée pour continuer..."
read a
#
echo pour phpmyadmin, choisir 'apache2' à configurer et MdP=admin
echo " puis OUI à la configuration ..."
sudo apt-get install -y  phpmyadmin
#
echo WIRINGPI
sudo apt-get install -y git git-core
cd ~
git clone git://git.drogon.net/wiringPi
cd ~/wiringPi
git pull origin
sudo su
./build
#
echo Passez à install2.sh
echo avant de rebooter
#