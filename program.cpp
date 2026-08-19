#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
 
LiquidCrystal_I2C lcd(0x27, 16, 2); 
 
const int greenLED = 2; 
const int yellowLED = 3; 
const int redLED = 4; 
const int voltagePin = A0; 
 
const float VOLTAGE_RATIO = 5.0;   // Calibrate this value if needed 
 
float readBattery() { 
  long sum = 0; 
 
  for (int i = 0; i < 20; i++) { 
    sum += analogRead(voltagePin); 
    delay(2); 
  } 
 
  float adc = sum / 20.0; 
  float vout = adc * 5.0 / 1023.0; 
 
  return vout * VOLTAGE_RATIO; 
} 
 
void setup() { 
 
  pinMode(greenLED, OUTPUT); 
  pinMode(yellowLED, OUTPUT); 
  pinMode(redLED, OUTPUT); 
 
  lcd.init(); 
  lcd.backlight(); 
 
  lcd.setCursor(0, 0); 
  lcd.print("Pedal Power"); 
 
  lcd.setCursor(0, 1); 
  lcd.print("Initializing"); 
 
  delay(1500); 
} 
 
void loop() { 
 
  float batt = readBattery(); 
  String status; 
 
  // Turn all LEDs OFF first 
  digitalWrite(greenLED, LOW); 
  digitalWrite(yellowLED, LOW); 
  digitalWrite(redLED, LOW); 
 
  // Battery Status 
  if (batt >= 13.2) { 
    status = "READY"; 
    digitalWrite(greenLED, HIGH); 
  } 
  else if (batt > 11.5) { 
    status = "CHARGING"; 
    digitalWrite(yellowLED, HIGH); 
  } 
  else { 
    status = "LOW BAT"; 
    digitalWrite(redLED, HIGH); 
  } 
 
  // LCD Display 
  lcd.clear(); 
 
  lcd.setCursor(0, 0); 
  lcd.print("Battery:"); 
  lcd.print(batt, 2); 
  lcd.print("V"); 
 
  lcd.setCursor(0, 1); 
  lcd.print(status); 
 
  delay(500); 
}