#include "EncoderController.h"

#define IS_AXIS_VALID(axis) ((axis) >= 0 && (axis) <= 5)

void EncoderController::init() {
    getConnectedEncoders();

    for (int i = 0; i < 6; ++i) {
        if (isEncoderConnected(i)) {
            setDataLine(i + 2);
            startPositions[i] = getRawData(i);
        }
    }
}

double EncoderController::getRawData(int axis) {
    if (IS_AXIS_VALID(axis)) {
        sendData(0x0D);

        while (Wire.available() == 0);
        unsigned int lowByte = Wire.read();

        sendData(0x0C);

        while (Wire.available() == 0);
        word highByte = Wire.read();
        highByte = highByte << 8;

        return (highByte | lowByte) * 0.087890625;
    } else
        return -1;
}

void EncoderController::getEncoderData(int axis) volatile {
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
        positions[axis] = ((numberOfTurns[axis] * 360) + correctedAngle) * 0.04449785;
    }
}

void EncoderController::updateEncodersValues() volatile {
    for (int i = 0; i < 6; ++i) {
        if (isEncoderConnected(i)) {
            setDataLine(i + 2);
            getEncoderData(i);
        }
    }
}

__attribute__((unused)) double EncoderController::getPosition(int axis) volatile {
    if (IS_AXIS_VALID(axis))
        return positions[axis];
    else
        return -1;
}

void EncoderController::getConnectedEncoders() {
    for (uint8_t dataLine = 0; dataLine < 8; dataLine++) {
        setDataLine(dataLine);

        Wire.beginTransmission(54); //address 0x36
        if (!Wire.endTransmission()) {
            encodersStatuses[dataLine - 2] = 1;
        }
    }
}

void EncoderController::sendData(int message) {
    Wire.beginTransmission(ENCODER_ADDR);
    Wire.write(message);
    Wire.endTransmission();
    Wire.requestFrom(ENCODER_ADDR, 1);
}

void EncoderController::setDataLine(uint8_t line) {
    if (line < 8) {
        Wire.beginTransmission(MULTIPLEXER_ADDR);
        Wire.write(1 << line);
        Wire.endTransmission();
    }
}

bool EncoderController::isEncoderConnected(int axis) volatile {
    return encodersStatuses[axis] == 1;
}

void EncoderController::printConnectedEncoders() {
    Serial.println("Connected encoders:");
    Serial.println("-------------------");
    Serial.println("PORT | CONNECTED");
    for (int i = 0; i < 6; i++) {
        Serial.print(i + 1);
        Serial.print("    | ");
        Serial.println(encodersStatuses[i] == 1 ? "YES" : "NO");
    }
    Serial.println("-------------------");
}

void EncoderController::printCurrentPositions() {
    for (double position : positions) {
        Serial.print(position);
        Serial.print(", ");
    }
    Serial.println("");
}
