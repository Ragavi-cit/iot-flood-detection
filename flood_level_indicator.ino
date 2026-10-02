// ESP32 FLOOD Level Indicator with 16x2 I2C LCD

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// FLOOD level sensors
#define SENSOR_30 34
#define SENSOR_60 35
#define SENSOR_100 32

// LEDs
#define GREEN_LED 25
#define YELLOW_LED 26
#define RED_LED 27

// Buzzer
#define BUZZER 14

void setup() {
  Serial.begin(115200);

  pinMode(SENSOR_30, INPUT);
  pinMode(SENSOR_60, INPUT);
  pinMode(SENSOR_100, INPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // LCD start
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("FLOOD Level");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
}

void loop() {

  int level30 = digitalRead(SENSOR_30);
  int level60 = digitalRead(SENSOR_60);
  int level100 = digitalRead(SENSOR_100);

  // All OFF
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  lcd.clear();

  // 100% FULL
  if (level100 == HIGH) {

    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH);

    lcd.setCursor(0, 0);
    lcd.print("FLOOD Level:");
    lcd.setCursor(0, 1);
    lcd.print("FULL - 100%");

    Serial.println("FLOOD Level: 100% - FULL");
  }

  // 60%
  else if (level60 == HIGH) {


    digitalWrite(YELLOW_LED, HIGH);

    lcd.setCursor(0, 0);
    lcd.print("FLOOD Level:");
    lcd.setCursor(0, 1);
    lcd.print("60% - MEDIUM");

    Serial.println("FLOOD Level: 60%");
  }

  // 30%
  else if (level30 == HIGH) {

    digitalWrite(GREEN_LED, HIGH);

    lcd.setCursor(0, 0);
    lcd.print("FLOOD Level:");
    lcd.setCursor(0, 1);
    lcd.print("30% - LOW");

    Serial.println("FLOOD Level: 30%");
  }

  // Empty
  else {

    lcd.setCursor(0, 0);
    lcd.print("FLOOD Level:");
    lcd.setCursor(0, 1);
    lcd.print("EMPTY");

    Serial.println("FLOOD Level: LOW");
  }

  delay(500);
}
