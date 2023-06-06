# Smart-Battery-Logger
The objective of this project is to make a device that can read battery voltage and it's inventory ID from an RFID sticker,
and log the data with a timestamp to a cloud database. From the database, we can extrapolate useful data like battery charge cycles, and predict the degradation of the battery.


## Introduction
This project involves the use of an Arduino and a raspberry pi.
The arduino is responsible for reading the voltage, and reading the inventory ID of the battery from it's RFID sticker. <br>
The raspberry Pi is responsible for adding a timestamp to the data and uploading it to the cloud. <br>


## Hardware Requirements

- Arduino board (e.g., Arduino Uno)
- Raspberry Pi (any model with GPIO pins)
- RFID reader module (compatible with the Arduino)
- LiPo batteries with RFID tags


## Software Implementation
### Raspberry Pi
*Set up the aws api*
'''
$ sudo pip install boto3
$ sudo pip install awscli
$ sudo pip install pyserial

'''
Configure aws api with the access key ID and access key genereated for the user
'''
aws configure
'''
Once everythin is installed,run the rasperry pi script

### Arduino
- Install the MFRC522 Library
- Upload the code in ArduinoCode.ino

##Hardware Implementation
The arduino is connected to the Rasperry pi via the USB ports on both.<br>
Arduino is connected to the RC522 RFID reader via SPI.<br>
In my case, the batteries being used were 3S or 4S LiPo, Which meant hte voltage would be more than what teh arduino can handle directly.
As a workaround, I used a simple voltage divider circuit to ensure that the voltage fed to the arduino never exceeds 5V.
