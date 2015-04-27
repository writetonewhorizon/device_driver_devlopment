#!/bin/sh
sudo insmod ./modules/scull.ko
sudo modinfo ./modules/scull.ko
lsmod
dmesg
sudo rm -f /dev/scull[0-3]
sudo mknod /dev/scull0 c 250 0
sudo mknod /dev/scull1 c 250 1
sudo mknod /dev/scull2 c 250 2
sudo mknod /dev/scull3 c 250 3
sudo ln -sf scull0 /dev/scull
sudo chgrp dharmender /dev/scull[0-3]
sudo chmod 644 /dev/scull[0-3]
ls -al /dev/ | grep scull
sudo ./sculltest
#dmesg
#sudo rmmod scull
#dmesg
#sudo modprobe -r scull or rmmod --help
