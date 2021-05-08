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
public:
    static void init();

    static void moveStepper(int axis);

    static void setDirection(int pin, bool type);

    static void moveAxis(int axis, bool dir);
};


#endif //OCTO2_0_STEPPERCONTROLLER_H
