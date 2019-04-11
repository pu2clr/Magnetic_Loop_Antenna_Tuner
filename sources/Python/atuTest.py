#!/usr/bin/env python
# -*- coding: utf-8 -*-
# This program was based on the example presented in the module pyserial.
# Yoy have to install pyserial module. To do that run: python -m pip install pyserial
#
# Antenna Tuner Controller Test.
# To execute this program type python atuTest.py
#
# ATTENTION: The communication port have to be configured correctly.
#
# Ricardo Caratti - 10/11/2013
# PU2CLR

import serial

atu = serial.Serial(
# Set your communication port to /dev/tty.xxxx (Unix like) or COMx (Microsoft Windows)
port='/dev/tty.HC-05-DevB', 
#        port='COM5',
        baudrate=9600,
        parity=serial.PARITY_ODD,
        stopbits=serial.STOPBITS_TWO,
        bytesize=serial.SEVENBITS
)

print ('Enter with ATU command or type finish.')
print (' +   =>  small step fine-tune capacitor/servo clockwise (pin 8)')
print (' -   =>  small step fine-tune capacitor/servo counterClockwise  (pin 8)')
print (' r   =>  medium step main capacitor/servo  clockwise  small step (pin 9)')
print (' R   =>  large step  main capacitor/servo  clockwise  large step (pin 9)')
print (' L   =>  large step  main capacitor/servo  counterClockwise large step (pin 9)')
print (' M   =>  the two capacitor/servo go to maximum position (about 180 degree)')
print (' m   =>  the two capacitor/servo go to minimum position (0 degree)')
print (' C   =>  the two capacitor/servo go to center position (about 90 degree)')
print (' S   =>  auto-scan. it needs a SWR meter connected to Arduino A3 pin')
print (' F   =>  switch to fine-tune. The LED of the rotary encoder might turn on')

atu.close()
atu.open()
atu.isOpen()

input=1
while 1 :
        input = raw_input("ATU command: ")
        if input == 'finish':
                atu.close()
                exit()
        else:
                atu.write(input)

