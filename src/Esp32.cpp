#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 12

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

LiquidCrystal_I2C lcd(0x27, 20, 4);  // LCD 20x4

void setup() {

  Serial.begin(115200);

  sensors.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Suhu Monitor");

  delay(1000);
}

void loop() {

  sensors.requestTemperatures();

  float tempC = sensors.getTempCByIndex(0);

  // Serial Monitor
  Serial.print("Suhu: ");
  Serial.print(tempC);
  Serial.println(" C");

  // LCD
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("SUHU MONITOR");

  lcd.setCursor(0, 1);
  lcd.print("Suhu : ");

  lcd.print(tempC);
  lcd.print(" C");

  delay(1000);
}