#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#include <map>
// RFID Module Pins
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define SS_PIN D4
#define RST_PIN D3
#define SERVO_PIN D8

// Track entry time in milliseconds
std::map<String, unsigned long> entryTimes;
MFRC522 rfid(SS_PIN, RST_PIN); // Create RFID instance
Servo myServo; // Create Servo instance

// Define valid RFID tag UID (Replace this with your own tag's UID)
// byte validUID[] = {0xC7, 0xB8, 0x36, 0x02}; // Replace with your RFID tag UID
void setup() {
    Serial.begin(9600);
    SPI.begin(); 
    rfid.PCD_Init(); 
    myServo.attach(SERVO_PIN); // Servo connected to Pin 6
    myServo.write(0); // Initial position (locked)

    Serial.println("Scan RFID Tag...");
      Wire.begin(D2, D1);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Smart Parking");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan RFID Tag...");
}

void loop() {
    // Check if an RFID card is present
    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
        return; // No card detected, exit loop
    }

    Serial.print("RFID Tag UID: ");
    String udi = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
        Serial.print(rfid.uid.uidByte[i], HEX);
        Serial.print(" ");
    udi += String(rfid.uid.uidByte[i], HEX);
    }
    udi.toUpperCase();
    lcd.clear();
      lcd.setCursor(0, 0);
  lcd.print("Tag found...");
    Serial.println();
    delay(500);
    // Check if the scanned UID matches the valid UID
    if (checkValidTag(rfid.uid.uidByte, rfid.uid.size)) {
          if (entryTimes.find(udi) == entryTimes.end()) {
          Serial.println("Access Granted! Unlocking...");
      unsigned long entryTime = millis();
    entryTimes[udi] = entryTime;
  lcd.clear();
          lcd.setCursor(0, 0);
  lcd.print("Entry granted");

        myServo.write(90); // Unlock (move servo)
        
            delay(3000); // Small delay to avoid excessive CPU usage
        // Wait until the card is removed
        while (isSameCardPresent()) {
            Serial.println("Card still present...");
            delay(1500); // Small delay to avoid excessive CPU usage
        }
    lcd.clear();
          lcd.setCursor(0, 0);
  lcd.print("Card removed!");
          lcd.setCursor(0, 1);
  lcd.print("Locking ....");

        Serial.println("Card removed! Locking...");
        myServo.write(0); // Lock again

  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan RFID Tag...");
        }else{
          Serial.println("Return detected...");
 unsigned long exitTime = millis();
    unsigned long entryTime = entryTimes[udi];
    unsigned long durationMillis = exitTime - entryTime;
    float durationHours = durationMillis / 3600000.0; // convert ms to hr

    // Calculate charge
    int charge = ceil(durationHours*60 * 5); // round up
      lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Exit Detected");
    lcd.setCursor(0, 1);
    lcd.print("Charge: Rs " + String(charge));

    Serial.println("Parking Duration: " + String(durationHours, 2) + " hrs");
    Serial.println("Charge: Rs " + String(charge));

    delay(3000);
    entryTimes.erase(udi); // clear record

        myServo.write(90); // Unlock (move servo)
        
            delay(3000); // Small delay to avoid excessive CPU usage
        // Wait until the card is removed
        while (isSameCardPresent()) {
            Serial.println("Card still present...");
            delay(1500); // Small delay to avoid excessive CPU usage
        }
    lcd.clear();
          lcd.setCursor(0, 0);
  lcd.print("Card removed!");
          lcd.setCursor(0, 1);
  lcd.print("Locking ....");

        Serial.println("Card removed! Locking...");
        myServo.write(0); // Lock again

  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan RFID Tag...");
        }
    } else {
        Serial.println("Access Denied!");
    }
 rfid.PICC_HaltA();        // Stop communication with card
    rfid.PCD_StopCrypto1();   // Stop encryption
    // rfid.PCD_Init();          // Reinitialize the RFID reader (IMPORTANT)
    delay(50);   
}

// Function to check if the scanned UID is valid
bool checkValidTag(byte* uid, byte size) {
    // for (byte i = 0; i < size; i++) {
    //     if (uid[i] != validUID[i]) {
    //         return false;
    //     }
    // }
    return true;
}

// Function to check if the same card is still present
bool isSameCardPresent() {
    if (!rfid.PICC_IsNewCardPresent()) {
        return false; // No card detected, meaning it was removed
    }

    if (!rfid.PICC_ReadCardSerial()) {
        return false; // Failed to read, assume removed
    }

    // Compare UID with last scanned UID
    // for (byte i = 0; i < rfid.uid.size; i++) {
    //     if (rfid.uid.uidByte[i] != validUID[i]) {
    //         return false; // Different card detected
    //     }
    // }

    return true; // Same card still present
}