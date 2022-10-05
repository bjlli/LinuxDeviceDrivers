# LinuxDeviceDrivers

Device tree based driver for a common cathode seven-segments display. To run this module in any embedded dispositive you should modify the device-tree overlay file, this repository shows an overlay example for the raspberry pi single board computer family.    

# Raspberry Pi pinout

The relation between the Raspberry Pi GPIO pins and the display segments is:

      SEGMENT | HS-3161 PIN | GPIO
         a    |     10      |  2
         b    |     9       |  3
         c    |     8       |  4
         d    |     5       |  5
         e    |     4       |  6
         f    |     2       |  7
         g    |     3       |  9
         dp   |     7       |  10
         
# Driver files

The driver files are located at /sys/class/7segment repository. If you write a number from 0 to 9 in the value file the display will show this number, for numbers higher than 9 the display will show the character "E" from error. If you write 0 and 1 in the enableDP file, the dot will respectively light off and light on. Writing numbers higher than 1 in the enableDP file shouldn't change anything at the display.

# To enable/disable the module

To enable the module in rasbian you should:

make

sudo dtoverlay overlay.dtbo

sudo insmod 7segment.ko

To disable the module in raspbian you should:

sudo rmmod 7segment
