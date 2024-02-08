#include "potentiometer.h"
#include <Arduino.h>

Potentiometer::Potentiometer(int pin) : pin(pin) {
    pinMode(pin, INPUT);
}

int Potentiometer::getValue() {
    return analogRead(pin);
}
