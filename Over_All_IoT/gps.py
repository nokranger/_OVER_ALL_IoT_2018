import RPi.GPIO as GPIO
import serial
import time

from time import sleep
ser = serial.Serial('/dev/ttyS0');
ser.close()
ser.open()
        
        
while True:
    try:
        read = ser.readline().decode().strip('\r\n');
        #read2 = ser.readline().decode().strip('\r\n');
        
        #r = read.split('MC')[1];
        #r2 = read2.split('TP')[1];
        print(read);
        #print(read2);
    except:
        pass
