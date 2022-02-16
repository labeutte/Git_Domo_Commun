#!/bin/bash
# version du 04/03/2019

echo Copie des fichiers de configuration ...

#dhcpcd
sudo mv /etc/dhcpcd.conf /etc/dhcpcd-ini.conf
sudo cp conf/dhcpcd.conf /etc/

#interface
sudo mv /etc/network/interfaces /etc/network/interfaces-ini
sudo cp conf/interfaces /etc/network

#hostapd (ssid/mdp du wifi)
sudo cp conf/hostapd.conf /etc/hostapd/
sudo mv /etc/default/hostapd /etc/default/hostapd-ini
sudo cp conf/hostapd /etc/default/

#dnsmasq (dhcp du wifi)
sudo mv /etc/dnsmasq.conf /etc/dnsmasq-ini.conf
sudo cp conf/dnsmasq.conf /etc/

#le RTC
sudo mv /etc/modules /etc/modules.ini
sudo cp conf/modules /etc/
sudo mv /boot/config.txt /boot/config.txt.ini
sudo cp /conf/config.txt /boot/
sudo mv /etc/rc.local /etc/rc.local.ini
sudo cp conf/rc.local /etc/
sudo mv /lib/udev/hwclock-set /lib/udev/hwclock-set.ini
sudo cp conf/hwclock-set /lib/udev/
sudo chmod a+x /lib/udev/hwclock-set
