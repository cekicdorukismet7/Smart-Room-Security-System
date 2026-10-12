# Smart Room Security System (IoT & Embedded C++)

Hello! I am a passionate Technical High School student at **Yahya Gunsur Vocational and Technical Anatolian High School**, specializing in Information Technology and Software Development. I completed my primary education at **METU Development Foundation Schools**, building a strong analytical and English foundation (B2 Level). 

I have been building hands-on Arduino and hardware projects since the 6th grade. This repository features my advanced Smart Room Security System, blending embedded development with smart automation protocols.

## Key Features & Engineering Architecture

- **Non-Blocking Code (`millis()`):** Unlike standard beginner projects that freeze the microcontroller with `delay()`, this system uses asynchronous time-tracking via `millis()`. This allows the system to monitor sensors while simultaneously processing serial commands.
- **Persistent Data Logging (`EEPROM`):** Built-in fault tolerance ensures that the total security event count (`olaySayisi`) is securely saved onto the microcontroller's EEPROM. If the power cuts out, the data is preserved.
- **Live Terminal Control:** Features an interactive serial interface. Users can query the system status (`durum`), check logs (`olay`), or reset memory (`sifirla`) dynamically.
- **Dynamic Threat Visualizer:** Features an adaptive LED alert loop that increases its frequency (flashing speed) dynamically as the threat duration escalates.
- **Fault-Tolerant Ultrasonic Sensor Handling:** Implemented error boundaries where sensor timeout outputs are caught (`sure == 0`) and filtered out to prevent systemic system loops.

##  Hardware Components
- Arduino Microcontroller
- HC-SR04 Ultrasonic Distance Sensor
- Sound Detection Sensor (Digital Input)
- LED Visual Status Indicators

##  Tech Stack
- **Languages:** Embedded C / C++, Python (for automation frameworks)
- **Concepts:** IoT Architecture, Fault-tolerant Embedded Logic, Serial Communication, Memory Management

---
*Feel free to reach out to me for innovative IoT prototypes and clean embedded systems development!*
