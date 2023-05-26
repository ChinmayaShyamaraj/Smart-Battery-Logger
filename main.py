import reader
import serial
import time
import cloud



ser=serial.Serial('/dev/ttyUSB0',9600,timeout=1)
ser.reset_input_buffer()

while True:
	line=ser.readline().decode('utf-8')
	if len(line)>0:
		line=line.split()
		voltage=float(line[1])
		print(line[0],voltage)
		cloud.upload(line[0],voltage)
#reader.readRFID()
