# LCD1602
Orange Pi Bit Bash of the LCD1602 module

3 programs are included..

lcd.cpp which provides a command line interface to send commands or data to the LCD1602

disp.cpp which allows you to send a string of data to the LCD from the command line  date | ./disp  OR  disp Hello

demo.cpp which is a demo of 2 lines doing a reverse scroll..

Note that I borrowed the wiringPi.c program from https://github.com/xpertsavenue/WiringOP-Zero/issues/18 but modified it slightly to accomoate the orange Pi Zero Plus2 H5.  This git has been tested with the Orange Pi Zero 256M and 512M versions as well as the Plus2 H3 and H5. A branch for the Raspberry Pi Zero W is also available.

A non-technical blog is available at http://artsayler.blogspot.com/p/mexico.html
