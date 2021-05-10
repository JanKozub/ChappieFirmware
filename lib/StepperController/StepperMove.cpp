#include "StepperMove.h"

StepperMove::StepperMove(int axis, bool direction) : axis(axis), direction(direction) {}

StepperMove::StepperMove() {
    axis = 0;
    direction = true;
}
