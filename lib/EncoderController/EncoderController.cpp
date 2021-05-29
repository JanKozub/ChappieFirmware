#include "EncoderController.h"

#define IS_AXIS_VALID(axis) ((axis) >= 0 && (axis) <= 5)

void EncoderController::init() {
    for (int i = 0; i < 5; ++i) {
        startPositions[i] = getRawData(i);
    }
}

double EncoderController::getRawData(int axis) volatile {
    if (IS_AXIS_VALID(axis)) {
        sendData(addresses[axis], 0x0D);

        while (Wire.available() == 0);
        unsigned int lowByte = Wire.read();

        sendData(addresses[axis], 0x0C);

        while (Wire.available() == 0);
        word highByte = Wire.read();
        highByte = highByte << 8;

        return (highByte | lowByte) * 0.087890625;
    } else
        return -1;
}

void EncoderController::getDataFromEncoder(int axis) volatile {
    if (IS_AXIS_VALID(axis)) {
        double correctedAngle = getRawData(axis) - startPositions[axis];
        if (correctedAngle < 0)
            correctedAngle = correctedAngle + 360;

        int quadrantNumber = 0;

        if (correctedAngle >= 0 && correctedAngle <= 90)
            quadrantNumber = 1;
        else if (correctedAngle > 90 && correctedAngle <= 180)
            quadrantNumber = 2;
        else if (correctedAngle > 180 && correctedAngle <= 270)
            quadrantNumber = 3;
        else if (correctedAngle > 270 && correctedAngle < 360)
            quadrantNumber = 4;

        if (quadrantNumber != previousQuadrantNumber[axis]) {
            if (quadrantNumber == 1 && previousQuadrantNumber[axis] == 4) {
                numberOfTurns[axis]++;
            }

            if (quadrantNumber == 4 && previousQuadrantNumber[axis] == 1) {
                numberOfTurns[axis]--;
            }
            previousQuadrantNumber[axis] = quadrantNumber;
        }
        positions[axis] = (((numberOfTurns[axis] * 360) + correctedAngle) * 0.24) * 0.24;
    }
}

double EncoderController::getPosition(int axis) volatile {
    if (IS_AXIS_VALID(axis))
        return positions[axis];
    else
        return -1;
}

void EncoderController::sendData(int address, int message) {
    Wire.beginTransmission(address);
    Wire.write(message);
    Wire.endTransmission();
    Wire.requestFrom(address, 1);
}