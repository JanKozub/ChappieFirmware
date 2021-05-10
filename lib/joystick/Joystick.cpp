#include "Joystick.h"

//AXIS 1-6 PINS
uint8_t joystickPins[] = {32, 33, 35, 36, 34, 39};

void Joystick::init() {
    for (uint8_t pin: joystickPins)
        pinMode(pin, INPUT);
}

int Joystick::getJoystickVal(int axis) {
    return analogRead(joystickPins[axis]);
}

void Joystick::debugJoystick() {
    Serial.println(
            String(getJoystickVal(joystickPins[0])) + " | " +
            String(getJoystickVal(joystickPins[1])) + " | " +
            String(getJoystickVal(joystickPins[2])) + " | " +
            String(getJoystickVal(joystickPins[3])) + " | " +
            String(getJoystickVal(joystickPins[4])) + " | " +
            String(getJoystickVal(joystickPins[5]))
    );
}

int* Joystick::getStates() {
    static int states[6];
    for (int i = 0; i < 6; ++i) {
        states[i] = Joystick::getJoystickState(Joystick::getJoystickVal(i));
    }
    return states;
}

int Joystick::getJoystickState(int var) {
    if (var == 0)
        return 0;
    if (var == 4095)
        return 1;
    return -1;
}
