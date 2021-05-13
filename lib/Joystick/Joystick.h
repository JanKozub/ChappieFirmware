#include "Arduino.h"

#ifndef OCTO2_0_JOYSTICK_H
#define OCTO2_0_JOYSTICK_H

class Joystick {
public:
    static void init();

    static int getJoystickVal(int pin);

    static void debugJoystick();

    static int getJoystickState(int var);

    static int *getStates();
};


#endif //OCTO2_0_JOYSTICK_H
