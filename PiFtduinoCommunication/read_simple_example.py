import serial
import time

ser = serial.Serial('/dev/ttyACM0', 9600)
time.sleep(10)
while ser.in_waiting:
    print(ser.readline())
