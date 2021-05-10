#ifndef CHAPPIEFIRMWARE_STEPPERMOVE_H
#define CHAPPIEFIRMWARE_STEPPERMOVE_H


class StepperMove {
public:
    int axis{};
    bool direction{};

    StepperMove(int axis, bool direction);

    StepperMove();
};


#endif //CHAPPIEFIRMWARE_STEPPERMOVE_H
