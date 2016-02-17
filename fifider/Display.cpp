#include "Display.hpp"

Display& Display::getInstance(void){
    static Display instance;
    return instance;
}

void Display::initialize(void) {
    _data_pin = HW_SR_DATA_PIN;
    _clock_pin = HW_SR_CLOCK_PIN;
    _latch_pin = HW_SR_LATCH_PIN;
    _num_digits = HW_DISP_DIGITS;

    pinMode(_clock_pin, OUTPUT);
    pinMode(_latch_pin, OUTPUT);
    pinMode(_data_pin, OUTPUT);
}

void Display::shiftByte(unsigned char data) {
    int i;
    int pin_state;

    for (i=7; i>=0; i--)  {
        digitalWrite(_clock_pin, 0);
        pin_state = data & (1<<i);
        digitalWrite(_data_pin, pin_state);
        digitalWrite(_clock_pin, 1);
        digitalWrite(_data_pin, 0);
    }

    digitalWrite(_clock_pin, 0);
}

void Display::out(void){
    for(int i = 0 ; i < _num_digits ; i++){
        digitOut(i);
    }
}

void Display::digitOut(unsigned char digit) {
    digitalWrite(_latch_pin, 0);
    shiftByte(1<<digit);
    shiftByte(_digit_data[digit]);
    digitalWrite(_latch_pin, 1);
}

void Display::setDigit(unsigned int idx, int num){
    int data = 0;

    if(num == 0){
        data = HW_DISP_0;
    }else if(num == 1){
        data = HW_DISP_1;
    }else if(num == 2){
        data = HW_DISP_2;
    }else if(num == 3){
        data = HW_DISP_3;
    }else if(num == 4){
        data = HW_DISP_4;
    }else if(num == 5){
        data = HW_DISP_5;
    }else if(num == 6){
        data = HW_DISP_6;
    }else if(num == 7){
        data = HW_DISP_7;
    }else if(num == 8){
        data = HW_DISP_8;
    }else if(num == 9){
        data = HW_DISP_9;
    }
    _digit_data[idx] = data;
}
