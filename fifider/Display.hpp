#ifndef FIFIDER_DISPLAY_HPP
#define FIFIDER_DISPLAY_HPP

#include "hardware.hpp"
#include "Arduino.h"

class Display{
    public:
        static Display& getInstance(void);

        Display(Display const&);
        void operator=(Display const&);

        void initialize(void);

        void setDigit(unsigned int idx, int num);
        unsigned char getDigit(unsigned int idx){return _digit_data[idx];}

        void out(void);

    private:
        Display() {};

        void shiftByte(unsigned char data);

        void digitOut(unsigned char display);

        int _data_pin, _clock_pin, _latch_pin;
        unsigned int _num_digits;
        unsigned char _digit_data[HW_DISP_DIGITS];
        unsigned char _segment_map[16];
};

#endif //FIFIDER_DISPLAY_HPP
