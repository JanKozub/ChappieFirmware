#include "Arduino.h"
#include "../Pinout.h"

#ifndef CHAPPIEFIRMWARE_SHIFTREGISTER_H
#define CHAPPIEFIRMWARE_SHIFTREGISTER_H

class ShiftRegister {
public:

    static void init();

    static void setDirPin(int axis, bool state);

    static void setEnPin(int axis, bool state);

private:

    static void writeReg(int pin, bool state);
};


#endif //CHAPPIEFIRMWARE_SHIFTREGISTER_H
