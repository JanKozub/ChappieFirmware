#include "StepperController.h"

Joystick joystick;
ShiftRegister shiftRegister;

void StepperController::init() {
    joystick.init();
    shiftRegister.init();

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
        shiftRegister.setDirPin(steppers[i].axis, steppers[i].direction);
    }

    StepperController::stepSteppers(steppers, numOfSteppers);
}

void StepperController::controlWithJoystick() {
    StepperMove moves[6];
    int *states = joystick.getStates();
    int movesCounter = 0;
    for (int i = 0; i < 6; ++i) {
        if (states[i] != -1) {
            moves[movesCounter] = StepperMove(i, states[i] == 0);
            movesCounter++;
        }
    }

    StepperController::moveSteppers(moves, movesCounter);
}

void StepperController::rotateByDegree(StepperMove stepperMove, int degree) {
    shiftRegister.setDirPin(stepperMove.axis, (uint8_t) stepperMove.direction);

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
    shiftRegister.setEnPin(axis, false);
}

void StepperController::disableStepper(int axis) {
    shiftRegister.setEnPin(axis, true);
}
