//based on examples from Aruino's Liquid Crystal Hello World, IoT Digital Loggers' relay example, and the distance sensor examples. All linked below.
//https://github.com/pololu/vl53l1x-arduino
//https://docs.arduino.cc/learn/electronics/lcd-displays
//http://www.digital-loggers.com/iot2faqs.html

#include <Wire.h>
#include "VL53L1X.h"

VL53L1X Distance_Sensor;

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int relay = 13;

void setup()
{
  Wire.begin();
  Wire.setClock(400000); // use 400 kHz I2C

  Serial.begin(9600);
  Serial.println("VL53L1X Distance Sensor tests in long distance mode(up to 4m).");
  Distance_Sensor.setTimeout(500);
  if (!Distance_Sensor.init())
  {
    Serial.println("Failed to initialize VL53L1X Distance_Sensor!");
    while (1);
  }

  Distance_Sensor.setDistanceMode(VL53L1X::Long);
  //I know its stupid long but it works so cope harder
  Distance_Sensor.setMeasurementTimingBudget(500000);
  Distance_Sensor.startContinuous(1000);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(relay, OUTPUT);      // Initialize the Atmel GPIO pin as an output
}

void loop()
{
  Distance_Sensor.read();
  int distance_mm = Distance_Sensor.ranging_data.range_mm;

  Serial.print("Distance(mm): ");
  Serial.println(distance_mm);

  // Clear the LCD display and set the cursor to the first row
  lcd.clear();
  lcd.setCursor(0, 0);

  // Print the distance on the LCD
  lcd.print("Distance(mm):");
  lcd.setCursor(0, 1);
  lcd.print(distance_mm);

  if (distance_mm < 1000){
    digitalWrite(relay, HIGH);   // Turn the relay off
  }
  else{
    digitalWrite(relay, LOW);   // Turn the relay on 
  }
  
}
