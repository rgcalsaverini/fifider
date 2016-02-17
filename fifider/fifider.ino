#include "FiFider.hpp"

void setup(){
    FiFider::getInstance().begin();
}

void loop() {
    FiFider::getInstance().checkState();
}
