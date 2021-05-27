#include "Arduino.h"

#ifndef OCTO2_0_JOYSTICK_H
#define OCTO2_0_JOYSTICK_H

class Joystick {
private:
    uint8_t joystickPins[6] = {32, 33, 35, 36, 34, 39};

    static int getJoystickState(int var);
public:

    void init();

    int getJoystickVal(int pin);

    void debugJoystick();

    int *getStates();
};


#endif //OCTO2_0_JOYSTICK_H
