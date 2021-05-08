#include "Joystick.h"
#include "Arduino.h"

void Joystick::init() {
    for (int pin: joystickPins)
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

int Joystick::getJoystickState(int var) {
    if (var == 0)
        return 0;
    if (var == 4095)
        return 1;
    return -1;
}
