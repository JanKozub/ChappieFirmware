#include "Arduino.h"

#ifndef CHAPPIEFIRMWARE_SHIFTREGISTER_H
#define CHAPPIEFIRMWARE_SHIFTREGISTER_H

#define latchPin 27
#define clockPin 26
#define dataPin 25

class ShiftRegister {
public:

    void init();

    void setDirPin(int axis, bool state);

    void setEnPin(int axis, bool state);

private:

    void writeReg(int pin, bool state);
};


#endif //CHAPPIEFIRMWARE_SHIFTREGISTER_H
