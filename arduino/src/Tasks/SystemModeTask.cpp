#include <Arduino.h>
#include "config.h"
#include "components/servo_motor_impl.h"
#include "components/MyLCD.h"
#include "components/ButtonImpl.h"
#include "Tasks/SystemModeTask.h"
#include "MsgService.h"

SystemModeTask::SystemModeTask(){
    this->state = AUTOMATIC; 
    
    MsgService.init();
    pinMode(3, HIGH);
    this->servo = new ServoMotorImpl(SERVO_PIN);
    this->lcd = new MyLCD(0x27, 8, 2);
    this->button = new ButtonImpl(BUTTON_PIN);
    this->potentiometer = new Potentiometer(POT_PIN);
    
    servo->on();
    servo->setPosition(0);
    lcd->initialize();
    lcd->clearDisplay();

    openingLevel = 0;  //SOLO PER DEBUG, VA LETTO DALLA SERIALE (VEDI SOTTO)
    
}

void SystemModeTask::tick() {
    switch(state) {
        case AUTOMATIC:
            
            /**leggere dalla seriale l'apertura della valvola*/
            if (MsgService.isMsgAvailable()) {
                Msg* msg = MsgService.receiveMsg();    
                oldOpeningLevel = openingLevel;
                openingLevel = msg->getContent().toDouble();    
                /* NOT TO FORGET: message deallocation */
                delete msg;
            }
            

        


            lcd->clearDisplay();
            lcd->printMessage(openingLevel);
            lcd->printMessage(", Automatic");
            
            servo->setPosition(openingLevel);
    
            
            if (debouncedButtonPress()) {
                this->setState(MANUAL);
            }
            break;

        case MANUAL:
            Serial.println("Manual");
            openingLevel = potentiometer->getValue();
            lcd->clearDisplay();
            lcd->printMessage(openingLevel);
            lcd->printMessage(", Manual");

            servo->setPosition(openingLevel);
            
            if (debouncedButtonPress()) {
                this->setState(AUTOMATIC);
            }
            break;
    }
}

bool SystemModeTask::debouncedButtonPress() {
    static unsigned long lastDebounceTime = 0;
    static const unsigned long debounceDelay = 50; // Tempo di debounce in millisecondi
    static int lastButtonState = LOW;

    unsigned long currentMillis = millis();
    
    if (currentMillis - lastDebounceTime > debounceDelay) {
        // Leggi lo stato del pulsante
        int buttonState = button->isPressed();
        
        // Se lo stato del pulsante è cambiato
        if (buttonState != lastButtonState) {
            lastDebounceTime = currentMillis;
            
            // Se il nuovo stato del pulsante è HIGH (premuto)
            if (buttonState == HIGH) {
                lastButtonState = buttonState;
                return true; // Rilevato un pressione stabile
            }
        }
    }
    
    lastButtonState = button->isPressed();
    return false; // Nessuna pressione stabile rilevata
}

void SystemModeTask::setState(int newState) {
    state = newState;
}
