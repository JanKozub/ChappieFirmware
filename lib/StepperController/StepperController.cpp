#include "StepperController.h"
#include "Arduino.h"

int pulsePins[6] = {12, 4, 26, 5, 23, 17};
int dirPins[6] = {14, 15, 25, 19, 21, 16};
int enPins[6] = {27, 2, 13, 18, 22, 420};

void StepperController::init() {
    for (int pulsePin : pulsePins)
        pinMode(pulsePin, OUTPUT);

    for (int dirPin: dirPins)
        pinMode(dirPin, OUTPUT);

    for (int enPin : enPins)
        pinMode(enPin, OUTPUT);
}

void StepperController::moveStepper(int axis) {
    digitalWrite(pulsePins[axis], HIGH);
    delayMicroseconds(100);
    digitalWrite(pulsePins[axis], LOW);
    delayMicroseconds(100);
}

void StepperController::setDirection(int pin, bool type) {
    digitalWrite(pin, type);
}

void StepperController::moveAxis(int axis, bool dir) {
    StepperController::setDirection(dirPins[axis], dir);
    StepperController::moveStepper(axis);
}
