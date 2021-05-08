#include "Arduino.h"
#include "../lib/joystick/Joystick.h"
#include "../lib/StepperController/StepperController.h"


void controlWithJoystick() {
    for (int i = 0; i < 6; ++i) {
        int js = Joystick::getJoystickState(Joystick::getJoystickVal(i));
        if (js != -1) StepperController::moveAxis(i, js == 0);
    }
}

void setup() {
    Serial.begin(9600);
    Joystick::init();
    StepperController::init();
}

void loop() {
    controlWithJoystick();
}
