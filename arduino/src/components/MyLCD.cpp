// MyLCD.cpp
#include "MyLCD.h"
#include <Arduino.h>

MyLCD::MyLCD(int address, int columns, int rows) : lcd(address, columns, rows) {}

void MyLCD::initialize() {
  lcd.init();
  lcd.backlight();
  pinMode(9, OUTPUT);
  analogWrite(9, 50);
  lcd.setCursor(0, 0);
}

void MyLCD::printMessage(const char *message) {
  lcd.print(message);
}

void MyLCD::printMessage(double message) {
  lcd.print(message);
}

void MyLCD::clearDisplay() {
  lcd.clear();
}
