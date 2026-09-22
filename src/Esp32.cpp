#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "secrets.h"

#define ONE_WIRE_BUS 35

//lcd
#define SDA_PIN 22
#define SCL_PIN 21

//potentiometer
#define PH_PIN 34

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {

  Serial.begin(115200);

  //i2c 
  Wire.begin(SDA_PIN, SCL_PIN);

  //ds
  sensors.begin();

  //lcd
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("   WATER MONITOR");

  delay(2000);
  lcd.clear();
}

void loop() {

  //read suhu
  sensors.requestTemperatures();

  float tempC = sensors.getTempCByIndex(0);

  
  //potentiometer
  int adcValue = analogRead(PH_PIN);

  
  float voltage = (adcValue / 4095.0) * 3.3;

  //tegangan ke ph
  float pH = (voltage / 3.3) * 14.0;


  String status;

  if (pH < 6.5) {
    status = "Asam";
  }
  else if (pH <= 7.5) {
    status = "Netral";
  }
  else {
    status = "Basa";
  }

  Serial.print("ADC   : ");
  Serial.println(adcValue);

  Serial.print("Volt  : ");
  Serial.println(voltage, 2);

  Serial.print("pH    : ");
  Serial.println(pH, 2);

  Serial.print("Suhu  : ");
  Serial.print(tempC, 2);
  Serial.println(" C");

  Serial.println();

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("   WATER MONITOR");

  lcd.setCursor(0, 1);
  lcd.print("Temperature: ");
  lcd.print(tempC, 1);
  lcd.print(" C");

  lcd.setCursor(0, 2);
  lcd.print("pH          : ");
  lcd.print(pH, 2);

  lcd.setCursor(0, 3);
  lcd.print("Status      : ");
  lcd.print(status);

  delay(1000);
}