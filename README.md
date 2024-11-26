# diy-gps

A DIY GPS navigator built using ESP32, uBlox Neo M8N GPS module, and an OLED display.

<p >
  <img src="https://github.com/user-attachments/assets/ce4a9ef7-76ae-41ab-954b-699d16465b3f" width="400" alt="DIY GPS Device">
</p>

## Features


- Real-time GPS tracking
- Display of latitude and longitude
- Altitude measurement
- Current speed in km/h
- Number of satellites connected
- Time display in IST (UTC+5:30)
- Debug mode via Serial Monitor

## Hardware Requirements

- ESP32 Development Board
- uBlox Neo M8N GPS with Compass
- 128x64 0.96 Inch OLED Display Module (I2C Interface)
- Breadboard
- Jumper Wires

All components were sourced from [robokits.co.in](https://robokits.co.in/)

## Cost Optimization

You can build this project in different ways depending on your needs:
- For basic tracking: Use cheaper GPS modules
- For high accuracy: Use uBlox Neo M8N
- Current build ($22) offers a great balance of cost and accuracy
- Total cost can range from $15-100 depending on component selection

## Quick Start Guide

1. **Gather Components**
   - Purchase all components listed above
   - Make sure you have a good USB cable for ESP32

2. **Hardware Assembly**
   - Connect GPS Module to ESP32:
     - Red wire: VCC → 3.3V
     - Black wire: GND → GND
     - Yellow wire: TX → GPIO16 (RX2)
   - Connect OLED Display to ESP32:
     - VCC → 3.3V
     - GND → GND
     - SCL → GPIO22
     - SDA → GPIO21

3. **Software Setup**
   - Install Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software)
   - Install ESP32 board support ([Guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html))
   - Install required libraries through Arduino Library Manager:
     - TinyGPS++
     - Adafruit_GFX
     - Adafruit_SSD1306

4. **Upload Code**
   - Open esp32-gps-navigator.ino in Arduino IDE
   - Select "ESP32 Dev Module" from Tools > Board menu
   - Choose correct COM port
   - Click Upload button

5. **First Run**
   - Take the device outdoors for better GPS signal
   - Wait for "GPS INIT..." message
   - First fix might take 1-2 minutes
   - Once connected, you'll see coordinates and other data

## Understanding the Display

```
Sats:7  Speed:0.0
51.5074         <- Latitude
-0.1278         <- Longitude
ALT:35m   13:45 <- Altitude & Time(IST)
```

## Troubleshooting

Common issues and solutions:
- No GPS fix: Make sure you're outdoors or near a window
- OLED not working: Check I2C connections and address
- No serial output: Verify correct baud rate (115200)
- GPS not responding: Double-check TX wire connection


## Future Goals

### Map Navigation
- Implementing local map rendering for navigation
- Custom MapForge parser written in Rust ([mapsforge-rs](https://github.com/ChetanXpro/mapsforge-rs))
  - This is a separate project to efficiently parse MapForge binary maps
  - Written in Rust for better performance and memory safety
  - Will be integrated with this GPS navigator for map rendering
- Custom renderer for OLED display
- This is a complex feature under development as it involves building several components from scratch

## Project Ecosystem
This project is part of a larger ecosystem:
1. **diy-gps**: Current project for basic GPS functionality (this repo)
2. **[mapsforge-rs](https://github.com/ChetanXpro/mapsforge-rs)**: Rust-based MapForge parser (in development)
3. Map renderer: Future component for navigation display


## Future Improvements

Possible enhancements you can try:
- Add map rendering for navigation (work in progress)
- Create a custom PCB design instead of using breadboard
- Add a battery for portable use
- Store coordinates in SD card
- Add a button to change display modes
- Connect to WiFi to log location
- Design a 3D printed case

## Important Notes

- This is a basic version that can be enhanced based on your needs
- Component quality affects GPS accuracy and fix time
- Consider soldering components on a PCB for permanent use
- The code is modular and can be adapted for different displays or GPS modules


## Debug Mode

For developers:
- Set `debugMode = true` in code
- Open Serial Monitor at 115200 baud
- View detailed GPS data stream

## Contributing

Feel free to fork this project and submit pull requests for any improvements.

## License

MIT License

## Support

If you need help:
- Open an issue in GitHub
- Review open/closed issues
- Contact me: chetanbaliyan10@gmail.com


---
*Note: This project is ideal for learning about GPS, ESP32, and I2C displays. Build responsibly!*
