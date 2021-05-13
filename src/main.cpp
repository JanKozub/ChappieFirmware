#include "Arduino.h"
#include "../lib/Joystick/Joystick.h"
#include "../lib/StepperController/StepperController.h"

void controlWithJoystick() {
    StepperMove moves[6];
    int *states = Joystick::getStates();
    int movesCounter = 0;
    for (int i = 0; i < 6; ++i) {
        if (states[i] != -1) {
            moves[movesCounter] = StepperMove(i, states[i] == 0);
            movesCounter++;
        }
    }

    StepperController::moveSteppers(moves, movesCounter);
}

void setup() {
    Serial.begin(9600);
    Joystick::init();
    StepperController::init();
    ShiftRegister::init();
}

void loop() {
    controlWithJoystick();
//    Joystick::debugJoystick();
}
