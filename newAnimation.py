#!/usr/bin/env python

import serial   # serielle Schnittstellen nutzbar
import sys      # Parameter

com = sys.argv[1]
rate = sys.argv[2]
speed = sys.argv[3]
frames = []
i = 0
while len(frames)<(len(sys.argv)-4) :
    frames.append(sys.argv[i+4])
    i=i+1 
ser = serial.Serial(com, 9600)
get = ser.readline();
if "<startsetup>" in get :
    ser.write('D')
    get = ser.readline()
    while "<startok>" not in get:
        print get
        get = ser.readline()
    ser.write('B')
    get = ser.readline()
    while "<startok>" not in get:
        print get
        get = ser.readline()
    ser.write('C1#1')
    get = ser.readline()
    while "<startok>" not in get:
        print get
        get = ser.readline()
    for f in frames :
        ser.write('F'+f)
        get = ser.readline()
        while "<startok>" not in get:
            print get
            get = ser.readline()
    ser.write('C'+rate+'#'+speed);
    get = ser.readline()
    while "<startok>" not in get:
        print get
        get = ser.readline()
