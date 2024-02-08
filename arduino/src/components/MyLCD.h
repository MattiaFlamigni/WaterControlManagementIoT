// MyLCD.h
#ifndef MYLCD_H
#define MYLCD_H

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

class MyLCD {
public:
  MyLCD(int address, int columns, int rows);
  void initialize();
  void printMessage(const char *message);
  void printMessage(double message);
  void clearDisplay();

private:
  LiquidCrystal_I2C lcd;
};

#endif  // MYLCD_H
