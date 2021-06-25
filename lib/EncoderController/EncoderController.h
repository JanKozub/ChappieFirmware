#include "Arduino.h"
#include "Wire.h"
#include "../Pinout.h"

#ifndef CHAPPIEFIRMWARE_ENCODERCONTROLLER_H
#define CHAPPIEFIRMWARE_ENCODERCONTROLLER_H

class EncoderController {

private:
    double startPositions[6] = {0, 0, 0, 0, 0, 0};
    double positions[6] = {0, 0, 0, 0, 0, 0};
    double numberOfTurns[6] = {0, 0, 0, 0, 0, 0};
    int previousQuadrantNumber[6] = {0, 0, 0, 0, 0, 0};
    int encodersStatuses[6] = {0, 0, 0, 0, 0, 0};

    static double getRawData(int axis);

    static void sendData(int message);

    static void setDataLine(uint8_t line);

    void getConnectedEncoders();

    void getEncoderData(int axis) volatile;

    bool isEncoderConnected(int axis) volatile;

public:

    void init();

    __attribute__((unused)) double getPosition(int axis) volatile;

    void updateEncodersValues() volatile;

    void printConnectedEncoders();

    void printCurrentPositions();
};


#endif //CHAPPIEFIRMWARE_ENCODERCONTROLLER_H
