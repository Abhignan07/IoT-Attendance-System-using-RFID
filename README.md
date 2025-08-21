# RFID-Based Attendance System using ESP8266 & Google Sheets

## About

This IoT-based project automates attendance tracking using RFID cards and a NodeMCU (ESP8266). Each scanned tag's roll number is instantly logged in a Google Sheet via Wi‑Fi, offering a reliable and cloud-accessible alternative to manual attendance systems.

---

## Features

- Real-time attendance logging
- Wireless data transfer using Wi‑Fi on ESP8266
- Cloud storage with Google Sheets
- Simple, scalable, and cost-effective approach

---

## Hardware Requirements

- NodeMCU ESP8266 (Wi‑Fi-enabled microcontroller)
- RC522 RFID reader module (SPI interface)
- RFID tags or cards (e.g., MIFARE Classic)
- Jumper wires and optionally a breadboard
- USB cable or 5V power source

---

## Software Requirements

- Arduino IDE with ESP8266 board package
- Libraries:
  - `MFRC522` — for RFID communication
  - `ESP8266WiFi` — for Wi-Fi connectivity
  - `ESP8266HTTPClient` — for HTTP requests
- Google Apps Script for linking to Google Sheets
- Google account for access and deployment of sheets

---

## Circuit Connections

| RC522 Pin | NodeMCU Pin |
| --------- | ----------- |
| SDA       | D2          |
| SCK       | D5          |
| MOSI      | D7          |
| MISO      | D6          |
| RST       | D1          |
| VCC       | 3.3V        |
| GND       | GND         |

---

## Setup & Usage

1. **Clone** this repo:

   git clone https://github.com/Abhignan07/IoT-Attendance-System-using-RFID.git

2. **Upload** `write_rfid_nodemcu.ino` to write roll numbers onto RFID tags.

3. **Generate** a new Google Sheet and open **Extensions → Apps Script**.

4. **Paste and deploy** your Google Apps Script as a Web App. Ensure:

   - **Execute as**: Me
   - **Access**: Anyone
   - Copy the Web App URL.

5. **Open** `send_data_to_google_sheet.ino`, update the `scriptURL` with your web app URL, then upload to your ESP8266.

6. **Scan** your RFID tag—attendance is marked in real time in your Google Sheet!

---

## Flow

RFID Tag Scan → ESP8266 Reads Roll Number → HTTPS Call to Google Apps Script → Google Sheet Appends Entry with Timestamp

---

## Real-World Use Cases

- School or college attendance
- Office or event check-ins
- Library book tracking
- Secure room access control

---

## Future Enhancements

- Add visual or buzzer feedback
- Integrate notifications (email/SMS)
- Build a dashboard for analytics
- Move backend to Firebase or a custom server

---

## Author

**Abhignan07**  
GitHub: [@Abhignan07](https://github.com/Abhignan07)  
Feel free to contribute or reach out with questions!

---

**Smart, reliable attendance powered by RFID & IoT**
