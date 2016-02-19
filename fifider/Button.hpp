#ifndef FIFIDER_BUTTON_HPP
#define FIFIDER_BUTTON_HPP

#include <stddef.h>
#include <Arduino.h>

class Button{
    public:
        Button(void){};

        void initialize(int pin, unsigned int debounce_ms=20, unsigned int hold_ms = 2000);

        void onDown(void (*on_down_callback)(void));

        void onUp(void (*on_up_callback)(void));

        void onHold(void (*on_hold_callback)(void));

        void check(void);

        void holdBlocksUp(bool value){_hold_blocks_up = value;}

        bool isPressed(void){return _pressed;}

    private:
        int _pin;
        unsigned int _debounce;
        unsigned int _hold_length;
        unsigned long _press_milis;
        bool _pressed;
        bool _down_called;
        bool _hold_called;
        bool _hold_blocks_up;
        unsigned int _hold_down_count;
        void (*_on_down_callback)(void);
        void (*_on_up_callback)(void);
        void (*_on_hold_callback)(void);

};

#endif //FIFIDER_HARDWARE_HPP
