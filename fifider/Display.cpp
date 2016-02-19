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

    _segment_map[0]= 0x3F;
    _segment_map[1]= 0x06;
    _segment_map[2]= 0x5B;
    _segment_map[3]= 0x4F;
    _segment_map[4]= 0x66;
    _segment_map[5]= 0x6D;
    _segment_map[6]= 0x7D;
    _segment_map[7]= 0x07;
    _segment_map[8]= 0x7F;
    _segment_map[9]= 0x67;
    _segment_map[10] /* A */ = 0x77;
    _segment_map[11] /* b */ = 0x7C;
    _segment_map[12] /* C */ = 0x39;
    _segment_map[13] /* d */ = 0x5E;
    _segment_map[14] /* E */ = 0x79;
    _segment_map[15] /* F */ = 0x71;
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
    _digit_data[idx] = _segment_map[num];
}
