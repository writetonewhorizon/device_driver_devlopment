#Build the driver (.ko file) by running make.
#Load the driver using insmod.
#List the loaded modules using lsmod.
#List the major number allocated, using cat /proc/devices.
#“null driver”-specific experiments e.g. sudo chmod a+w /dev/mynull , 
#sudo echo hi > /dev/mynull -> [open + write + close].
#sudo cat /dev/mynull -> [open + read + close].
#Unload the driver using rmmod.
#print the printk dmesg | tail -10

sudo dmesg -c		# to clean previous dmesg buffer
sudo insmod ./modules/char.ko
lsmod
dmesg
#sudo mknod /dev/char2 c 249 0
ls -al /dev/mynull
ls -al /sys/class/chardev/
sudo chmod a+w /dev/mynull
sudo echo hi > /dev/mynull
sudo cat /dev/mynull 
sudo rmmod char
dmesg

