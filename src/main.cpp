#include "Arduino.h"
#include "../lib/Joystick/Joystick.h"
#include "../lib/StepperController/StepperController.h"
#include "../lib/EncoderController/EncoderController.h"

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

EncoderController encoderController;

void setup() {
    Serial.begin(9600);
    Wire.begin();
    Wire.setClock(800000L);
    Joystick::init();
    StepperController::init();
    ShiftRegister::init();
    encoderController.init();
}

void loop() {
    encoderController.getDataFromEncoder(0);
//    controlWithJoystick();
//    Joystick::debugJoystick();
    Serial.println(encoderController.getPositions()[0]);
    delay(10);
}
