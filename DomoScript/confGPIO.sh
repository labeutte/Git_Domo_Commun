#!/bin/bash

sudo sh -c 'echo "22" > /sys/class/gpio/export &'
sleep 1

#gpio en sortie gpio3 = BCM22
#/usr/bin/gpio export 3 out #gpio3
sudo sh -c 'echo out > /sys/class/gpio/gpio22/direction'

# Init à 1 pour repos
sudo sh -c 'echo 1 > /sys/class/gpio/gpio22/active_low'

#initialisation ; position inverse mettre à 0
# gpio write <pi> <value>
#/usr/bin/gpio write 3 0
sudo sh -c 'echo  0 > /sys/class/gpio/gpio22/value'
