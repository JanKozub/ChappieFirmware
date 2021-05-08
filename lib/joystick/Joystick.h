#ifndef OCTO2_0_JOYSTICK_H
#define OCTO2_0_JOYSTICK_H

//AXIS 1-6 PINS
static const int joystickPins[6] = {32, 33, 35, 36, 34, 39};

class Joystick {
public:
    static void init();

    static int getJoystickVal(int pin);

    static void debugJoystick();

    static int getJoystickState(int var);
};


#endif //OCTO2_0_JOYSTICK_H
