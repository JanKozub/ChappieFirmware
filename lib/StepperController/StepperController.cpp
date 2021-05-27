#include "StepperController.h"

uint8_t pulsePins[] = {12, 4, 14, 5, 23, 17};
int microstepsTable[6] = {0, 0, 0, 42271, 42271, 42271}; //microsteps needed to rotate full 360 deg
int rotationSpeed = 40;
int dupa[] = {500, 450, 400, 350, 300, 250, 200, 150, 75, 50};

void StepperController::init() {
    for (uint8_t pulsePin : pulsePins)
        pinMode(pulsePin, OUTPUT);
}

void StepperController::stepStepper(int axis, int delay) {
    digitalWrite(pulsePins[axis], HIGH);
    delayMicroseconds(delay);
    digitalWrite(pulsePins[axis], LOW);
    delayMicroseconds(delay);
}

void StepperController::stepSteppers(StepperMove steppers[], int numOfSteppers) {
    for (int i = 0; i < numOfSteppers; ++i) {
        digitalWrite(pulsePins[steppers[i].axis], HIGH);
    }
    delayMicroseconds(1);
    for (int i = 0; i < numOfSteppers; ++i) {
        digitalWrite(pulsePins[steppers[i].axis], LOW);
    }
    delayMicroseconds(1);
}

void StepperController::moveSteppers(StepperMove steppers[], int numOfSteppers) {
    for (int i = 0; i < numOfSteppers; ++i) {
        ShiftRegister::setDirPin(steppers[i].axis, steppers[i].direction);
    }

    StepperController::stepSteppers(steppers, numOfSteppers);
}

void StepperController::rotateByDegree(StepperMove stepperMove, int degree) {
    ShiftRegister::setDirPin(stepperMove.axis, (uint8_t) stepperMove.direction);

    int pulseTime = 50;

    for (int i = 300; i > pulseTime; --i) { // PRZYSPIESZANIE
        for (int j = 0; j < 5; ++j) {
            StepperController::stepStepper(stepperMove.axis, i);
        }
    }

    for (int i = 0; i < (microstepsTable[stepperMove.axis] * (degree / 360.0)) - 2490; i++) { //TRZYMANIE PREDKOSCI
        StepperController::stepStepper(stepperMove.axis, pulseTime);
    }

    for (int i = pulseTime; i < 300; ++i) { //SPOWALNIANIE
        for (int j = 0; j < 5; ++j) {
            StepperController::stepStepper(stepperMove.axis, i);
        }
    }
}

void StepperController::enableStepper(int axis) {
    ShiftRegister::setEnPin(axis, false);
}

void StepperController::disableStepper(int axis) {
    ShiftRegister::setEnPin(axis, true);
}
