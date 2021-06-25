#include "Arduino.h"
#include "../lib/StepperController/StepperController.h"
#include "../lib/EncoderController/EncoderController.h"

EncoderController encoderController;
StepperController stepperController;

TaskHandle_t Core2Task;

[[noreturn]] void core2Task(void * pvParameters ){
    for (;;) {
        encoderController.updateEncodersValues();
    }
}


void setup() {
    Serial.begin(115200);
    Wire.begin();
    Wire.setClock(800000L);
    stepperController.init();
    encoderController.init();

    xTaskCreatePinnedToCore(core2Task,"core2Task",10000,nullptr,1,&Core2Task,1);

    encoderController.printConnectedEncoders();

    encoderController.printCurrentPositions();
}

void loop() {
    stepperController.controlWithJoystick();
//    encoderController.printCurrentPositions();
}
