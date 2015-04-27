#! /bin/bash
make
read v
cat <  /proc/devices
insmod ./modules/lkm.ko nod=10
read v
lsmod
read v
cat <  /proc/devices
read v
dmesg
read v
gcc -o appl1 appl1.c -lpthread
gcc -o appl1 appl2.c -lpthread
gcc -o appl1 appl3.c -lpthread
make ioctl_app
mknod node c 249 0
read v
./ioctl_app node
./appl1 node 
./appl2 node 
./appl3 node 
read v
ls -al
read v
cat <  /proc/devices
read v
vim /proc/dharam
vim /proc/jit
read v
rmmod lkm
cat <  /proc/devices
read v
unlink node
read v
dmesg
read v
cat < /proc/devices
exit 0
