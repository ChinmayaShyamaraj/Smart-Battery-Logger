
/* 
 * 
 *   RFID-RC522 (SPI connection)
 *   
 *   CARD RC522      Arduino (UNO)
 *     SDA  -----------  10 (Configurable, see SS_PIN constant)
 *     SCK  -----------  13
 *     MOSI -----------  11
 *     MISO -----------  12
 *     IRQ  -----------  
 *     GND  -----------  GND
 *     RST  -----------  9 (onfigurable, see RST_PIN constant)
 *     3.3V ----------- 3.3V
 *     
 */

  #include <SPI.h>
  #include <MFRC522.h>
  
  
  #define SS_PIN          10
  #define RST_PIN         9

  MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
  MFRC522::StatusCode status;        //variable to get card status
  
  byte buffer[18];                   //data transfer buffer (16+2 bytes data+CRC)
  byte size = sizeof(buffer);
  uint8_t pageAddr = 0x06;

  int R1=105,R2=33;
  
void setup() {
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card  
  
}

void loop() {

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
    return;
    
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
    return;
    
  //read the Inventory ID from the rfid tag
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(pageAddr, buffer, &size);
  
  //if there's any error, start over by returning out of the loop function
  
  if (status != MFRC522::STATUS_OK) 
    return;

  //if flow reaches here, then there is valid data read from the RFID tag

  //Create a string which will be appended with the data collected, and sent to the Raspberry Pi, add the Inventory ID previosly read from the RFID tag
  String toPi = String((char *)buffer);
  
  //Read the voltage from the battery
  int sensorValue = analogRead(A0);

  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (4.6 / 1023.0)*((R1+R2)/R2);
  
  toPi+=" "+String(voltage);

  //send the string to the Pi over serila connection
  Serial.println(toPi);

  mfrc522.PICC_HaltA();    
    
}
