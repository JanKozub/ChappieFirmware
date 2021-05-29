#include "StepperMove.h"
#include "Arduino.h"
#include "../Joystick/Joystick.h"
#include "../ShiftRegister/ShiftRegister.h"
#include "../EncoderController/EncoderController.h"

#ifndef OCTO2_0_STEPPERCONTROLLER_H
#define OCTO2_0_STEPPERCONTROLLER_H

#define AX1 0
#define AX2 1
#define AX3 2
#define AX4 3
#define AX5 4
#define AX6 5

#define FORWARD true
#define BACKWARD false

class StepperController {

private:
    void stepSteppers(StepperMove steppers[], int numOfSteppers);

    uint8_t pulsePins[6] = {12, 4, 14, 5, 23, 17};
    int microstepsTable[6] = {0, 0, 0, 42271, 42271, 42271}; //microsteps needed to rotate full 360 deg

public:

    void stepStepper(int axis, int delay);

    void init();

    void moveSteppers(StepperMove steppers[], int numOfSteppers);

    void controlWithJoystick();

    static void enableStepper(int axis);

    static void disableStepper(int axis);

    void rotateByDegree(StepperMove stepperMove, int degree);
};


#endif //OCTO2_0_STEPPERCONTROLLER_H
