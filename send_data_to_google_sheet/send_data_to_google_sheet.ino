#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>  // ✅ Needed for HTTPS

#define SS_PIN D2
#define RST_PIN D1

const char* ssid = "iPhone";         // Replace with your Wi-Fi SSID
const char* password = "Abhignan";   // Replace with your Wi-Fi password
const String scriptURL = "https://script.google.com/macros/s/AKfycbzpOXBuuCagVX53zEv0YnvVHZGN6JG0jwjuIe6eL0ssSBM_VfQdmy3Sh3-i5w2rrxf-/exec";

MFRC522 mfrc522(SS_PIN, RST_PIN);

WiFiClientSecure client;  // ✅ Secure client

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected!");

  client.setInsecure();  // ✅ Accept self-signed SSL certificates
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) return;

  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  byte buffer[18];
  byte size = sizeof(buffer);

  if (mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid)) == MFRC522::STATUS_OK) {
    if (mfrc522.MIFARE_Read(4, buffer, &size) == MFRC522::STATUS_OK) {
      String roll = "";
      for (int i = 0; i < 16; i++) {
        if (buffer[i] != 32) roll += (char)buffer[i];
      }

      Serial.println("Roll Number Read: " + roll);

      HTTPClient http;
      String fullURL = scriptURL + "?roll=" + roll;
      http.begin(client, fullURL);  // ✅ HTTPS with secure client

      int httpCode = http.GET();

      if (httpCode > 0) {
        Serial.println("HTTP Response Code: " + String(httpCode));
        String payload = http.getString();
        Serial.println("Server Response: " + payload);
      } else {
        Serial.println("HTTP Request Failed");
        Serial.println("Error: " + http.errorToString(httpCode));
      }

      http.end();
    }
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  delay(2000);
}
