#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BUTTON_1_PIN 2
#define BUTTON_2_PIN 3
#define BUTTON_3_PIN 4
#define BUZZER_PIN 5
#define IR_PIN 6
#define LED_STATUS_PIN 7

LiquidCrystal_I2C lcd(0x27, 16, 2);

//LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  pinMode(BUTTON_1_PIN, INPUT);
  pinMode(BUTTON_2_PIN, INPUT);
  pinMode(BUTTON_3_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_STATUS_PIN, OUTPUT);
  pinMode(IR_PIN, INPUT);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hold: ");
  lcd.setCursor(0, 1);
  lcd.print("Round: ");
}

void loop() {
  static int count, round = 0;
  if (!digitalRead(IR_PIN)) {
    digitalWrite(LED_STATUS_PIN, HIGH);
    while (!digitalRead(IR_PIN)) {
      delay(10);
    }
    if (count > 14) {
      digitalWrite(BUZZER_PIN, HIGH);
      round++;
      count = 0;
    } else {
      count++;
    }
    digitalWrite(LED_STATUS_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }
  if (!digitalRead(BUTTON_1_PIN)) {
    count = 0;
  }
  if (!digitalRead(BUTTON_2_PIN)) {
    round = 0;
  }
  if (!digitalRead(BUTTON_3_PIN)) {
    count = 0;
    round = 0;
  }
  lcd.setCursor(6, 0);
  lcd.print(count);
  lcd.setCursor(7, 1);
  lcd.print(round);
}
