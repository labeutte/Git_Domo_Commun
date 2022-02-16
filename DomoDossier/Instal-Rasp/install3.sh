#!/bin/bash
# install2.sh
# version du 04/03/2019
#
cd /home/pi/Instal-Rasp
dos2unix conf/*
dos2unix Scripts/*
dos2unix trivy/*
dos2unix Application-www/*
#
echo Copie des fichiers de configuration ...
#
# motion
#sudo mv /etc/motion/motion.conf /etc/motion/motion-ini.conf
#sudo cp conf/motion.conf /etc/motion/motion.conf
#sudo cp conf/thread1.conf /etc/motion/thread1.conf
#sudo cp conf/thread2.conf /etc/motion/thread2.conf
#sudo cp conf/thread3.conf /etc/motion/thread3.conf
#
#dhcpcd
sudo mv /etc/dhcpcd.conf /etc/dhcpcd-ini.conf
sudo cp conf/dhcpcd.conf /etc/
#
#interface
sudo mv /etc/network/interfaces /etc/network/interfaces-ini
sudo cp conf/interfaces /etc/network
#
#hostapd (ssid/mdp du wifi)
sudo cp conf/hostapd.conf /etc/hostapd/
sudo mv /etc/default/hostapd /etc/default/hostapd-ini
sudo cp conf/hostapd /etc/default/
#
#dnsmasq (dhcp du wifi)
sudo mv /etc/dnsmasq.conf /etc/dnsmasq-ini.conf
sudo cp conf/dnsmasq.conf /etc/
#
#le RTC
echo ds3231 0x68 | sudo tee /sys/class/i2c-adapter/i2c-1/new_device
sudo mv /etc/modules /etc/modules.ini
sudo cp conf/modules /etc/
sudo mv /boot/config.txt /boot/config-txt.ini
sudo cp /conf/config.txt /boot/
sudo mv /etc/rc.local /etc/rc-local.ini
sudo cp conf/rc.local /etc/
sudo chmod a+x /etc/rc.local
sudo mv /lib/udev/hwclock-set /lib/udev/hwclock-set.ini
sudo cp conf/hwclock-set /lib/udev/
sudo chmod a+x /lib/udev/hwclock-set
#
sudo mv /etc/ntp.conf /etc/ntp.conf.ini
sudo cp conf/ntp.conf /etc/
#
sudo cp conf/rtc-init.service /etc/systemd/system/
sudo cp conf/rtc-setup.sh /usr/lib/systemd/scripts/
sudo chmod a+x /usr/lib/systemd/scripts/rtc-setup.sh
sudo systemctl enable rtc-init
sudo mv /lib/udev/hwclock-set /lib/udev/hwclock-set.ini
sudo cp conf/hwclock-set /lib/udev/hwclock-set
sudo update-rc.d fake-hwclock disable
sudo apt-get -y remove fake-hwclock
sudo update-rc.d -f fake-hwclock remove
#
sudo cp conf/rc-local.service /etc/systemd/system/
#
#l'application
sudo mkdir /home/pi/script
sudo cp Scripts/*  /home/pi/script/
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
dos2unix /home/pi/trivy/*
#
sudo cp ../trivy/* /home/pi/trivy/
sudo chown pi.pi -R /home/pi/trivy
sudo chmod a+x /home/pi/trivy/appli

sudo hwclock -D -r

echo Fichiers de configuration copiés
echo Pensez à modifier cron : sudo crontab -e 
echo -> REBOOTEZ !
echo et faites 'sudo hwclock -D -r' pour vérifier l'heure

