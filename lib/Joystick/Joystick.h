#include "Arduino.h"
#include "../Pinout.h"

#ifndef OCTO2_0_JOYSTICK_H
#define OCTO2_0_JOYSTICK_H

class Joystick {
private:
    uint8_t joystickPins[6] = {JOYSTICK_PIN_1, JOYSTICK_PIN_2, JOYSTICK_PIN_3,
                               JOYSTICK_PIN_4, JOYSTICK_PIN_5, JOYSTICK_PIN_6};

    static int getJoystickState(int var);

public:

    void init();

    int getJoystickVal(int pin);

    void debugJoystick();

    int *getStates();
};


#endif //OCTO2_0_JOYSTICK_H
