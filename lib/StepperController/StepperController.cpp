#include "StepperController.h"

uint8_t pulsePins[] = {12, 4, 26, 5, 23, 17};
uint8_t dirPins[] = {14, 15, 25, 19, 21, 16};
uint8_t enPins[6] = {27, 2, 13, 18, 22, 60};
int microstepsTable[6] = {0, 0, 0, 6628, 40718, 0}; //microsteps needed to rotate full 360 deg

void StepperController::init() {
    for (uint8_t pulsePin : pulsePins)
        pinMode(pulsePin, OUTPUT);

    for (uint8_t dirPin: dirPins)
        pinMode(dirPin, OUTPUT);

    for (uint8_t enPin : enPins)
        pinMode(enPin, OUTPUT);
}

void StepperController::stepStepper(int axis) {
    digitalWrite(pulsePins[axis], HIGH);
    delayMicroseconds(100);
    digitalWrite(pulsePins[axis], LOW);
    delayMicroseconds(100);
}

void StepperController::stepSteppers(StepperMove steppers[], int numOfSteppers) {
    for (int i = 0; i < numOfSteppers; ++i) {
        digitalWrite(pulsePins[steppers[i].axis], HIGH);
    }
    delayMicroseconds(100);
    for (int i = 0; i < numOfSteppers; ++i) {
        digitalWrite(pulsePins[steppers[i].axis], LOW);
    }
    delayMicroseconds(100);
}

void StepperController::setDirection(int axis, uint8_t direction) {
    digitalWrite(dirPins[axis], direction);
}

void StepperController::moveSteppers(StepperMove steppers[], int numOfSteppers) {
    for (int i = 0; i < numOfSteppers; ++i) {
        StepperController::setDirection(steppers[i].axis, (uint8_t)steppers[i].direction);
    }

    StepperController::stepSteppers(steppers, numOfSteppers);
}

void StepperController::rotateByDegree(StepperMove stepperMove, int degree) {
    setDirection(stepperMove.axis, (uint8_t)stepperMove.direction);

    for (int i = 0; i < microstepsTable[stepperMove.axis] * (degree / 360.0); i++) {
        stepStepper(stepperMove.axis);
    }
}
