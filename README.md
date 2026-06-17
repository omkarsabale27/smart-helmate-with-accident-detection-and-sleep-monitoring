# smart-helmate-with-accident-detection-and-sleep-monitoring
Smart Helmet with Accident Detection and Sleep Monitoring System using Arduino UNO, MPU6050, IR Eye Blink Sensor, SIM800L GSM, and NEO-6M GPS. Detects rider drowsiness and accidents, sends real-time GPS location via SMS and call, improving road safety through an intelligent embedded system.
# 🛡 Smart Helmet with Accident Detection and Sleep Monitoring System

## 📖 Overview

The Smart Helmet with Accident Detection and Sleep Monitoring System is an intelligent embedded system designed to improve the safety of motorcycle riders. The project continuously monitors rider alertness using an IR eye-blink sensor and detects accidents using a vibration sensor and MPU6050 accelerometer/gyroscope.

If an accident occurs, the system automatically obtains the rider's GPS location and sends an emergency SMS and phone call using the SIM800L GSM module.

---

## 🎯 Objectives

- Detect rider drowsiness.
- Alert the rider using a buzzer.
- Detect road accidents.
- Send live GPS location.
- Notify emergency contacts automatically.
- Reduce accident response time.

---

# Features

- Sleep Detection
- Accident Detection
- GPS Tracking
- GSM Calling
- SMS Alert
- Real-time Monitoring
- Embedded System

---

# Hardware Used

- Arduino UNO
- MPU6050
- IR Eye Blink Sensor
- SW18010 Vibration Sensor
- NEO-6M GPS Module
- SIM800L GSM Module
- Buzzer
- Battery
- Helmet

---

# Software Used

- Arduino IDE
- Embedded C
- TinyGPS++
- MPU6050 Library

---

# Working

1. System initializes all sensors.
2. IR sensor monitors eye closure.
3. Eye closed for more than 5 seconds.
4. Buzzer alerts rider.
5. Vibration sensor detects impact.
6. MPU6050 detects helmet tilt.
7. GPS gets current location.
8. GSM calls rider.
9. If rider doesn't respond:
   - Calls emergency contact.
   - Sends GPS location through SMS.

---

# Advantages

- Low Cost
- Real Time
- Automatic Alert
- Easy Installation
- Accurate Accident Detection
- Rider Safety

---

# Applications

- Motorcycle Riders
- Delivery Riders
- Long Distance Travel
- Industrial Safety
- Smart Transportation

---

# Future Scope

- Mobile App
- IoT Cloud
- Alcohol Detection
- Voice Assistant
- Helmet Communication
- Vehicle Lock System

---

# Components

| Component | Cost |
|-----------|------|
| Arduino UNO | ₹500 |
| MPU6050 | ₹200 |
| IR Sensor | ₹80 |
| SIM800L | ₹500 |
| GPS Module | ₹450 |
| Vibration Sensor | ₹120 |
| Helmet | ₹1500 |
| Battery | ₹200 |

Total Cost = ₹3570

---

# Folder Structure

Smart-Helmet-Accident-Detection-System

├── Arduino_Code

├── Circuit_Diagram

├── Images

├── Project_Report

├── README.md

├── LICENSE

└── .gitignore

---

# Author

Omkar Sabale

B.Tech Electronics and Telecommunication Engineering

---

# License

MIT License
