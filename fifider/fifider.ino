#include "FiFider.hpp"
#include <Servo.h>
Servo servo;

void setup(){
    FiFider::getInstance().begin(servo);
}

void loop() {
    FiFider::getInstance().checkState(servo);
}
