#include "StepperController.h"

uint8_t pulsePins[] = {12, 4, 14, 5, 23, 17};
int microstepsTable[6] = {0, 0, 0, 6628, 40718, 0}; //microsteps needed to rotate full 360 deg

void StepperController::init() {
    for (uint8_t pulsePin : pulsePins)
        pinMode(pulsePin, OUTPUT);
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

void StepperController::moveSteppers(StepperMove steppers[], int numOfSteppers) {
    for (int i = 0; i < numOfSteppers; ++i) {
        ShiftRegister::setDirPin(steppers[i].axis, steppers[i].direction);
    }

    StepperController::stepSteppers(steppers, numOfSteppers);
}

void StepperController::rotateByDegree(StepperMove stepperMove, int degree) {
    ShiftRegister::setDirPin(stepperMove.axis, (uint8_t)stepperMove.direction);

    for (int i = 0; i < microstepsTable[stepperMove.axis] * (degree / 360.0); i++) {
        stepStepper(stepperMove.axis);
    }
}

void StepperController::enableStepper(int axis) {
    ShiftRegister::setEnPin(axis, false);
}

void StepperController::disableStepper(int axis) {
    ShiftRegister::setEnPin(axis, true);
}
