#include "StepperMove.h"
#include "Arduino.h"
#include "../ShiftRegister/ShiftRegister.h"

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
    static void stepStepper(int axis);

    static void stepSteppers(StepperMove steppers[], int numOfSteppers);

public:
    static void init();

    static void moveSteppers(StepperMove steppers[], int numOfSteppers);

    static void enableStepper(int axis);

    static void disableStepper(int axis);

    static void rotateByDegree(StepperMove stepperMove, int degree);
};


#endif //OCTO2_0_STEPPERCONTROLLER_H
