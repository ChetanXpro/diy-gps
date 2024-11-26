#include <TinyGPS++.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
TinyGPSPlus gps;
bool debugMode = true;

// Time zone offset for IST (UTC+5:30)
const int TIME_ZONE_OFFSET_HOURS = 5;
const int TIME_ZONE_OFFSET_MINUTES = 30;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, -1);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 failed"));
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.cp437(true);
  


  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(15, 20);
  display.println("GPS INIT...");
  display.display();
  delay(2000);
  
  if(debugMode) Serial.println("GPS Device Starting...");
}

void loop() {
  static unsigned long lastDisplay = 0;
  
  while (Serial2.available()) {
    if (gps.encode(Serial2.read())) {
      if (millis() - lastDisplay > 1000) {
        lastDisplay = millis();
        updateDisplay();
        if(debugMode) printStatus();
      }
    }
  }
}

// UTC to IST conversion
void getISTTime(int utc_hour, int utc_minute, int &ist_hour, int &ist_minute) {
  ist_minute = utc_minute + TIME_ZONE_OFFSET_MINUTES;
  ist_hour = utc_hour + TIME_ZONE_OFFSET_HOURS;
  
  if(ist_minute >= 60) {
    ist_hour += 1;
    ist_minute -= 60;
  }
  
  if(ist_hour >= 24) {
    ist_hour -= 24;
  }
}

void printStatus() {
  Serial.println("\n=== GPS Status ===");
  Serial.print("Satellites: ");
  Serial.println(gps.satellites.value());
  
  if (gps.location.isValid()) {
    Serial.print("Position: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(", ");
    Serial.println(gps.location.lng(), 6);
    
    if (gps.altitude.isValid()) {
      Serial.print("Altitude: ");
      Serial.print(gps.altitude.meters());
      Serial.println("m");
    }
  } else {
    Serial.println("Waiting for GPS fix...");
  }
  Serial.println("================");
}

void updateDisplay() {
  display.clearDisplay();
  
  if (gps.location.isValid()) {
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Sats:");
    display.print(gps.satellites.value());

  
    
    if (gps.speed.isValid()) {
      display.setCursor(64, 0);
      display.print("Speed:");
      display.print(gps.speed.kmph(), 1);
    }
    
   
    display.setTextSize(2);
    display.setCursor(0, 16);
    display.print(gps.location.lat(), 4);
    display.setCursor(0, 35);
    display.print(gps.location.lng(), 4);
    
    
    if (gps.altitude.isValid()) {
      display.setTextSize(1);
      display.setCursor(0, 56);
      display.print("ALT:");
      display.print(gps.altitude.meters(), 0);
      display.print("m");
    }
    
   
    if (gps.time.isValid()) {
      int ist_hour, ist_minute;
      getISTTime(gps.time.hour(), gps.time.minute(), ist_hour, ist_minute);
      
      display.setTextSize(1);
      display.setCursor(80, 56);
      if (ist_hour < 10) display.print("0");
      display.print(ist_hour);
      display.print(":");
      if (ist_minute < 10) display.print("0");
      display.print(ist_minute);
    }
    
  } else {

    display.setTextSize(2);
    display.setCursor(5, 10);
    display.println("Searching");
    display.setCursor(20, 30);
    display.println("GPS...");
    
    display.setTextSize(1);
    display.setCursor(0, 56);
    display.print("Sats: ");
    display.print(gps.satellites.value());
    
    if (gps.time.isValid()) {
      int ist_hour, ist_minute;
      getISTTime(gps.time.hour(), gps.time.minute(), ist_hour, ist_minute);
      
      display.setCursor(80, 56);
      if (ist_hour < 10) display.print("0");
      display.print(ist_hour);
      display.print(":");
      if (ist_minute < 10) display.print("0");
      display.print(ist_minute);
    }
  }
  
  display.display();
}