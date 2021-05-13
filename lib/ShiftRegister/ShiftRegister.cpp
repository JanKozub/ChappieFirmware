#include "ShiftRegister.h"

static int dirIndexes[] = {15, 2, 1, 10, 8, 12};
static int enIndexes[] = {14, 3, 0, 11, 9, 13};

static byte* registerState;

void ShiftRegister::init() {

    registerState = new byte[2];
    for (size_t i = 0; i < 2; i++) {
        registerState[i] = 0;
    }

    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
}

void ShiftRegister::writeReg(int pin, bool state) {
    int reg = pin / 8;

    digitalWrite(latchPin, LOW);
    for (int i = 0; i < 2; i++){
        byte* states = &registerState[i];
        if (i == reg){
            bitWrite(*states, pin - (8 * reg), state);
        }
        shiftOut(dataPin, clockPin, MSBFIRST, *states);
    }
    digitalWrite(latchPin, HIGH);
}

void ShiftRegister::setDirPin(int axis, bool state) {
    writeReg(dirIndexes[axis], state);
}

void ShiftRegister::setEnPin(int axis, bool state) {
    writeReg(enIndexes[axis], state);
}
