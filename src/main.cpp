#include "Arduino.h"
#include "../lib/StepperController/StepperController.h"
#include "../lib/EncoderController/EncoderController.h"

void controlWithJoystick() {
}

EncoderController encoderController;
StepperController stepperController;

void setup() {
    Serial.begin(9600);
    Wire.begin();
    Wire.setClock(800000L);
    stepperController.init();
    encoderController.init();
}

void loop() {
    stepperController.controlWithJoystick();
//    Joystick::debugJoystick();
    encoderController.getDataFromEncoder(0);
    Serial.println(encoderController.getPositions()[0]);
    delay(10);
}
