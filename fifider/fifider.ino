#include "FiFider.hpp"

void setup(){
    Serial.begin(9600);
    FiFider::getInstance().begin();
}

void loop() {
    FiFider::getInstance().checkState();
}
