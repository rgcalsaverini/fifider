#include "Button.hpp"

void Button::initialize(int pin, unsigned int debounce_ms, unsigned int hold_ms) {
    _pin = pin;
    _debounce = debounce_ms;
    _on_up_callback = NULL;
    _on_down_callback = NULL;
    _on_hold_callback = NULL;
    _hold_length = hold_ms;
    _press_milis = 0;
    _pressed = false;
    _hold_blocks_up = true;
    pinMode(_pin, INPUT);
}

void Button::check(void) {
    bool currently_pressed = (digitalRead(_pin) == 0);

    if(currently_pressed) {
        if(!_pressed) {
            _press_milis = millis();
            _pressed = true;
            _down_called = false;
            _hold_called = false;
        } else if(millis() - _press_milis > _debounce && _on_down_callback != NULL && !_down_called) {
            _on_down_callback();
            _down_called = true;
        } else if(millis() - _press_milis > _hold_length && _on_hold_callback != NULL && !_hold_called) {
            _on_hold_callback();
            _hold_called = true;
        }
    } else if(_pressed && millis() - _press_milis > _debounce){
        _pressed = false;

        if(_on_up_callback != NULL && (!_hold_blocks_up || !_hold_called)){
            _on_up_callback();
        }
    }
}

void Button::onDown(void (*on_down_callback)(void)) {
    _on_down_callback = on_down_callback;
}

void Button::onUp(void (*on_up_callback)(void)) {
    _on_up_callback = on_up_callback;
}
void Button::onHold(void (*on_hold_callback)(void)) {
    _on_hold_callback = on_hold_callback;
}
