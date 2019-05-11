#!/bin/bash

MCU=m328p
#MCU=atmega328p
CFG=/Applications/Arduino.app/Contents/Resources/Java/hardware/tools/avr/etc/avrdude.conf
PORT=/dev/cu.usbserial-A600K307
PRGM=arduino
#wiring
#arduino
#avrisp2          = Atmel AVR ISP mkII
#avrispmkII       = Atmel AVR ISP mkII

 
avrdude -C $CFG -F -v -v -p $MCU -c $PRGM -P $PORT -b 57600 -Uflash:r:"hdc1080-ccs811-lcd.hex":i



#-F                         Override invalid signature check.
#-v                         Verbose output. -v -v for more.
#-p <partno>                Required. Specify AVR device.
#-c <programmer>            Specify programmer type.
#-B <bitclock>              Specify JTAG/STK500v2 bit clock period (us).
#-D                         Disable auto erase for flash memory
#-P <port>                  Specify connection port.
#-b force baud rate 57600 needed for duemilanove ATMEGA 328 bootloader)
#

