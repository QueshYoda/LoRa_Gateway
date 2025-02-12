# LoRa-Based Distance Measurement System

## Overview
This project consists of two components:
1. **Sender Module**: Uses an ultrasonic sensor to measure distance and transmits data via LoRa.
2. **Gateway Module**: Receives LoRa data and sends it to ThingSpeak via WiFi.

## Hardware Requirements
- ESP32 or similar microcontroller
- Ra-01 (LoRa Module)
- HC-SR04 (Ultrasonic Sensor)
- WiFi Connection (for the gateway)

## Sender Module
### Description
The sender module measures the distance using an ultrasonic sensor and transmits it via LoRa.

### Wiring
| Component         | ESP32 Pin |
|------------------|-----------|
| LoRa NSS        | 13        |
| LoRa RESET      | 12        |
| LoRa DIO0       | 21        |
| LoRa MISO       | 5         |
| LoRa MOSI       | 4         |
| LoRa SCK        | 2         |
| Ultrasonic Trig | 17        |
| Ultrasonic Echo | 16        |

### Code Summary
- Initializes the LoRa module.
- Reads distance from the ultrasonic sensor.
- Sends the measured distance via LoRa.

## Gateway Module
### Description
The gateway module receives LoRa data and forwards it to ThingSpeak via WiFi.

### Wiring
| Component         | ESP32 Pin |
|------------------|-----------|
| LoRa NSS        | 13        |
| LoRa RESET      | 12        |
| LoRa DIO0       | 21        |
| LoRa MISO       | 5         |
| LoRa MOSI       | 4         |
| LoRa SCK        | 2         |

### Code Summary
- Connects to a WiFi network.
- Initializes LoRa to receive distance data.
- Forwards received data to ThingSpeak.

## Setup Instructions
1. Install the necessary libraries:
   - `LoRa.h`
   - `WiFi.h`
   - `SPI.h`
   - `Wire.h`
2. Configure the ThingSpeak API key in the gateway code.
3. Upload the sender and gateway sketches to their respective ESP32 boards.
4. Power up both modules and check the Serial Monitor for data transmission and reception.

## Usage
- The sender will measure distance and send it via LoRa.
- The gateway will receive the distance and upload it to ThingSpeak.
- View the data on ThingSpeak's dashboard.

## Troubleshooting
- Ensure both devices are powered on and using the same LoRa frequency.
- Check wiring connections for LoRa and ultrasonic sensors.
- Verify WiFi credentials in the gateway module.

## Future Enhancements
- Add an OLED display for real-time distance monitoring.
- Implement error handling for better data transmission reliability.
- Extend range with improved LoRa configurations.

---
This project demonstrates a simple IoT-based long-range communication system using LoRa and WiFi. 🚀

