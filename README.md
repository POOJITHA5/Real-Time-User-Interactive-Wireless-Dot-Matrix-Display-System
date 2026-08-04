# 📡 Real-Time User-Interactive Wireless Dot-Matrix Display System

## 🚀 Project Overview

This project implements a **wireless, real-time interactive display system** using multiple **8×8 dot-matrix LED displays** controlled via **Bluetooth communication**. The system allows users to send commands from a mobile device and dynamically control display patterns, text, time, and temperature.

📌 The system also integrates **real-time temperature monitoring** using an LM35 sensor.

---

## 🎯 Aim

To design and develop a system that:

* Displays customizable patterns on **four multiplexed dot-matrix displays**
* Supports **wireless control via Bluetooth (HC-05)**
* Integrates **real-time temperature monitoring**

---

## ✨ Features

* 📱 Wireless control via mobile (Bluetooth terminal app)
* 🔤 Fixed text display (4 characters)
* 🔁 Scrolling text display
* ✨ Blinking text mode
* ⏰ Real-time clock display (RTC)
* 🌡️ Temperature display using LM35 sensor
* 📝 Text editing via Bluetooth
* ⌚ Time & date editing functionality
* 💾 EEPROM storage for saved data

---

## 🧠 System Workflow

1. 🔌 On power ON, system reads mode from EEPROM
2. 📲 User interacts via Bluetooth terminal app
3. ⚙️ Menu-driven system allows selection:

   * Fixed string
   * Blinking string
   * Scrolling string
   * Time display
   * RTC scrolling display
   * Temperature display
   * Text edit mode
   * Time edit mode
4. 📡 Commands are received via UART (HC-05)
5. 💡 Selected output is displayed on LED matrix

---

## 🛠️ Hardware Requirements

* 🧩 LPC2148 Microcontroller
* 🔲 4 × 8×8 Dot Matrix Displays
* 🔌 74HC164 (Shift Register)
* 🔁 74HC573 (Latch IC)
* 💾 AT25LC512 EEPROM
* 📡 HC-05 Bluetooth Module
* 🌡️ LM35 Temperature Sensor
* 🔗 USB to UART Converter

---

## 💻 Software Requirements

* 💡 Embedded C
* 🧰 Keil µVision (Compiler)
* ⚡ Flash Magic (Programming Tool)

---

## 📁 Project Structure

```id="stru123"
Real-Time-User-Interactive-Wireless-Dot-Matrix-Display-System/
│
├── main.c                 # Entry point of the program
│
├── uart.c                 # UART (Bluetooth HC-05) communication
├── uart.h
│
├── dot_matrix.c           # Dot matrix display control logic
├── dot_matrix.h
│
├── rtc.c                  # Real-time clock handling
├── rtc.h
│
├── eeprom.c               # EEPROM read/write operations
├── eeprom.h
│
├── lm35.c                 # Temperature sensor (LM35) handling
├── lm35.h
│
├── delay.c                # Delay functions
├── delay.h
│
├── utils.c                # Helper functions
├── utils.h
```

---

## 🔗 Connections Overview

* Dot matrix controlled using:

  * **74HC164 → Column control**
  * **74HC573 → Row control**
* Bluetooth module connected via UART
* LM35 connected to ADC for temperature sensing

---

## ⚙️ Implementation Steps

1. 🔤 Display a single character on LED matrix
2. 🔡 Display 4-character string (e.g., HELP)
3. 🔁 Implement scrolling text (>10 characters)
4. 📡 Setup UART communication (Bluetooth)
5. 📋 Display menu on mobile app
6. 🎯 Implement display modes
7. ⏰ Integrate RTC for time display
8. 🌡️ Add LM35 sensor for temperature
9. 📝 Implement text editing
10. ⌚ Implement time editing

---

## 📊 Example Outputs

* 🔤 Fixed Text: `HELP`
* 🔁 Scrolling: `PROJECT SUCCESSFULLY COMPLETED`
* ⏰ Time: `09:30:23`
* 🌡️ Temperature: `30°C`

---

## 🔮 Future Scope

* 🌐 Upgrade to Wi-Fi / IoT connectivity
* ☁️ Cloud data logging
* 📊 Smart city display systems
* 🔐 Secure access with authentication
* 🎤 Voice-controlled display
* 📱 Custom mobile app interface

---

## 🙌 Conclusion

This project demonstrates a powerful combination of **embedded systems, wireless communication, and real-time data display**, making it ideal for applications like **public display boards, smart systems, and automation projects**.

