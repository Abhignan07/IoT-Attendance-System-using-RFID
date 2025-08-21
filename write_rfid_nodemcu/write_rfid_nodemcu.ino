#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN D2
#define RST_PIN D1
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) return;
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  byte block = 4;
  byte dataBlock[16] = {'B','2','0','1','6','3','8',' ',' ',' ',' ',' ',' ',' ',' ',' '};

  if (mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)) == MFRC522::STATUS_OK) {
    mfrc522.MIFARE_Write(block, dataBlock, 16);
    Serial.println("Written to RFID");
  }
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  delay(2000);
}