# Smart-Parking-System
Here’s a well-structured and detailed description of your **Smart Parking System** project suitable for documentation, reports, or presentations:

---

### 🚗 Smart Parking System – Project Description

The **Smart Parking System** is an automated solution designed to streamline vehicle entry, exit, and parking fee management using **RFID technology**, a **servo-controlled barrier**, and a **real-time display system**. Built around the **ESP8266 NodeMCU**, this system offers a cost-effective, user-friendly alternative to traditional parking solutions, particularly in gated communities, offices, and small commercial parking lots.

---

### 🔧 Key Components and Technologies
- **ESP8266 NodeMCU**: The microcontroller that powers the system and processes all logic.
- **MFRC522 RFID Reader**: Detects and reads unique RFID cards or tags used by vehicles.
- **Servo Motor**: Acts as a barrier gate, opening and closing based on RFID authorization.
- **I2C LCD Display (16x2)**: Displays system messages like access status, charges, and instructions.
- **C++ (Arduino)**: The programming language used to implement the embedded logic.
- **C++ STL Map**: Used to store entry timestamps of each user via their unique RFID UID.

---

### 🧠 How It Works

#### ✅ Entry Process
1. The system initializes with the message **"Scan RFID Tag..."** on the LCD.
2. When a valid RFID card is scanned:
   - The UID is read and stored with a timestamp.
   - LCD shows **"Entry granted"**, and the servo opens the gate.
   - After the card is removed, the gate automatically locks again.

#### 🚗 Exit Process
1. When the same card is scanned again (indicating exit):
   - The system calculates the **total parking duration** using the difference between current time and stored entry time.
   - **Charges are calculated** at ₹5 per minute (rounded up).
   - LCD displays **"Exit Detected"** and the calculated **parking fee**.
   - The gate opens to allow exit and then locks after card removal.
   - Entry data is cleared for future reuse.

#### 🚫 Invalid Cards
- Any card not matching the expected format or UID list can be denied access (validation logic is customizable).

---

### 💡 Features
- **Touchless entry/exit** with RFID cards.
- **Automated billing** based on duration of stay.
- **LCD-based feedback system** for real-time user interaction.
- **Security** via servo-controlled access gate.
- **Extendable**: Can be integrated with cloud databases, mobile apps, or IoT dashboards for large-scale deployment.

---

### 🧪 Potential Enhancements
- Store authorized UIDs in EEPROM or database.
- Add Wi-Fi connectivity for remote monitoring and logging.
- Send parking receipts to a mobile app via Firebase or HTTP.
- Integrate with payment gateways for automated billing.

---
