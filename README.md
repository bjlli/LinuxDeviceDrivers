# LinuxDeviceDrivers

Device tree based driver for a common cathode seven-segments display. To run this module in any embedded dispositive you should modify the device-tree overlay file, this repository shows an overlay example for the raspberry pi single board computer family.    

# Raspberry Pi pinout

The relation beetween the Raspberry Pi GPIO pins and the display segments is:

      SEGMENT | GPIO
         a    |   2
         b    |   3
         c    |   4
         d    |   5
         e    |   6
         f    |   7
         g    |   9
         dp   |   10
         
# Driver files

The driver files are located at /sys/class/7segment repository. If you write a number from 0 to 9 in the value file the display will show this number, for numbers higher than 9 the display will show the character "E" from error. If you write 0 and 1 in the enable_dp file, the dot will respectively light off and light on. Writing numbers highter than 1 in the enable_dp file shouldn't change anything at the display.

# To enable/disable the module

To enable the module in rasbian you should:

make

sudo dtoverlay overlay.dtbo

sudo insmod 7segment.ko

To disable the module in raspbian you should:

sudo rmmod 7segment
