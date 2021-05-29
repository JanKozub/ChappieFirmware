#include "Arduino.h"
#include "Wire.h"

//ENCODER AS5600
//DEFAULT ADDRESS 0x36

#ifndef CHAPPIEFIRMWARE_ENCODERCONTROLLER_H
#define CHAPPIEFIRMWARE_ENCODERCONTROLLER_H


class EncoderController {

private:
    double startPositions[6] = {0, 0, 0, 0, 0, 0};
    double positions[6] = {0, 0, 0, 0, 0, 0};
    double numberOfTurns[6] = {0, 0, 0, 0, 0, 0};
    int addresses[6] = {0x36, 0x36, 0x36, 0x36, 0x36, 0x36};
    int previousQuadrantNumber[6] = {0, 0, 0, 0, 0, 0};

    static void sendData(int address, int message);

public:
    void init();

    double getPosition(int axis) volatile;

    double getRawData(int axis) volatile;

    void getDataFromEncoder(int axis) volatile;
};


#endif //CHAPPIEFIRMWARE_ENCODERCONTROLLER_H
