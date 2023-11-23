#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BUTTON_1_PIN 2
#define BUTTON_2_PIN 3
#define BUTTON_3_PIN 4
#define BUZZER_PIN 5
#define IR_PIN A3
#define LED_STATUS_PIN 7

static int count = 0, rounds= 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);
  pinMode(BUTTON_3_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_STATUS_PIN, OUTPUT);
  pinMode(IR_PIN, INPUT);

  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hold: ");
  lcd.setCursor(0, 1);
  lcd.print("Round: ");
  digitalWrite(BUZZER_PIN, HIGH);
}

void loop() {
  if (digitalRead(IR_PIN)) {
    digitalWrite(LED_STATUS_PIN, HIGH);
    while (digitalRead(IR_PIN)) {
      buttonsFunction();
    }
    if (count > 14) {
      digitalWrite(BUZZER_PIN, LOW);
      lcd.setCursor(6, 0);
      lcd.print("  ");
      lcd.setCursor(7, 1);
      lcd.print("  ");
      delay(100);
      rounds++;
      count = 1;
    } else {
      count++;
    }
    digitalWrite(LED_STATUS_PIN, LOW);
    digitalWrite(BUZZER_PIN, HIGH);
  }
  buttonsFunction();
}

void buttonsFunction(){
  if (!digitalRead(BUTTON_1_PIN)) {
    lcd.setCursor(6, 0);
    lcd.print("  ");
    lcd.setCursor(7, 1);
    lcd.print("  ");
    count = 0;
  }
  if (!digitalRead(BUTTON_2_PIN)) {
    lcd.setCursor(6, 0);
    lcd.print("  ");
    lcd.setCursor(7, 1);
    lcd.print("  ");
    rounds = 0;
  }
  if (!digitalRead(BUTTON_3_PIN)) {
    lcd.setCursor(6, 0);
    lcd.print("  ");
    lcd.setCursor(7, 1);
    lcd.print("  ");
    count = 0;
    rounds = 0;
  }
  lcd.setCursor(6, 0);
  lcd.print(count);
  lcd.setCursor(7, 1);
  lcd.print(rounds);
}
