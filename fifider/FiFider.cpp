#include "FiFider.hpp"
#include "TimerOne.h"
#include <Arduino.h>
#include <avr/wdt.h>

unsigned long FiFider::_eta = HW_DEF_INTERVAL;
unsigned long FiFider::_interval = HW_DEF_INTERVAL;
unsigned char FiFider::_portion = HW_DEF_PORTION;
FiFider::FeederState FiFider::_feeder_state = FST_WAITING;
FiFider::DisplayState FiFider::_display_state = DST_ETA;
unsigned long FiFider::_ui_timestamp = 0;
unsigned long FiFider::_hold_init = 0;
bool FiFider::_is_holding = false;
bool FiFider::_hold_increase = true;
unsigned int FiFider::_hold_down_count = HW_HOLD_INC_CNT;

FiFider& FiFider::getInstance(void) {
    static FiFider instance;
    return instance;
}

void FiFider::begin(void) {
    if(!Memory::getInstance().isReady()) {
        _eta = HW_DEF_INTERVAL;
        _interval = HW_DEF_INTERVAL;
        _portion = HW_DEF_PORTION;
        FiFider::getInstance().saveState();
        Memory::getInstance().initialize();
    }else{
        loadState();
    }

    _feeder_state = FST_WAITING;
    _display_state = DST_ETA;

    Timer1.initialize(1000000);
    Timer1.attachInterrupt(FiFider::timerOverflow);

    _increase_btn.initialize(HW_BTN_INCR_PIN, 20, 800);
    _increase_btn.onUp(FiFider::increaseButton);
    _increase_btn.onHold(FiFider::holdIncreaseButton);
    _increase_btn.holdBlocksUp(false);

    _decrease_btn.initialize(HW_BTN_DECR_PIN, 20, 800);
    _decrease_btn.onUp(FiFider::decreaseButton);
    _decrease_btn.onHold(FiFider::holdDecreaseButton);
    _decrease_btn.holdBlocksUp(false);

    _select_btn.initialize(HW_BTN_SEL_PIN);
    _select_btn.onUp(FiFider::selectButton);
    _select_btn.onHold(FiFider::holdSelectButton);

    wdt_enable(WDTO_1S);

    Display::getInstance().initialize();

}

void FiFider::saveState(void) {
    Memory::getInstance().write(HW_ETA_ADDR, FiFider::getEta(), HW_ETA_BYTES);
    Memory::getInstance().write(HW_INTERVAL_ADDR, FiFider::getInterval(), HW_INTERVAL_BYTES);
    Memory::getInstance().write(HW_PORTION_ADDR, FiFider::getPortion(), HW_PORTION_BYTES);
}

void FiFider::loadState(void) {
    _eta = Memory::getInstance().readLong(HW_ETA_ADDR, HW_ETA_ADDR+HW_ETA_BYTES);
    _interval = Memory::getInstance().readLong(HW_INTERVAL_ADDR, HW_INTERVAL_ADDR+HW_INTERVAL_BYTES);
    _portion = Memory::getInstance().readLong(HW_PORTION_ADDR, HW_PORTION_ADDR+HW_PORTION_BYTES);
}

void FiFider::timerOverflow(void) {
    if(_feeder_state == FST_FEEDING) {
        FiFider::getInstance().setEta(0);
    }else if(_feeder_state == FST_WAITING) {
        FiFider::getInstance().setEta(FiFider::getInstance().getEta()-1);

        if(FiFider::_eta <= 0) {
            FiFider::_feeder_state = FST_FEEDING;
            FiFider::getInstance().setEta(FiFider::getInstance().getInterval());
        }

        if(FiFider::_eta%HW_SAVE_INTERVAL == 0)
            FiFider::getInstance().saveState();
    }
}

void FiFider::checkState(void) {
    wdt_reset();
    _increase_btn.check();
    _decrease_btn.check();
    _select_btn.check();

    if(_feeder_state == FST_WAITING) {
        if(_is_holding){
            if(millis() - _hold_init >= HW_HOLD_INCR1 && _hold_down_count > 0  || (millis() - _hold_init >= HW_HOLD_INCR2 && _hold_down_count == 0)){
                changeAmount(_hold_increase);
                _ui_timestamp = millis();
                _hold_init = millis();
                _hold_down_count -= _hold_down_count > 0 ? 1 : 0;
            }
        }

        if(_display_state == DST_ETA) {
            showEta();
        }else if(_display_state == DST_INTERVAL) {
            showInterval();
        }else if(_display_state == DST_PORTION) {
            showPortion();
        }
    } else if(_feeder_state == FST_FEEDING) {
        //TODO Actuate servo here and move sate change there
        _feeder_state = FST_WAITING;

    } else {
        _feeder_state = FST_WAITING;
    }

    if(_display_state != DST_ETA && millis() - _ui_timestamp > HW_DSP_TIMEOUT)
        _display_state = DST_ETA;

    Display::getInstance().out();

}

void FiFider::showEta(void) {
    if(_eta >= 3600) {
        Display::getInstance().setDigit(0, (FiFider::getEta()/36000) % 99);
        Display::getInstance().setDigit(1, (FiFider::getEta()/3600) % 10);
        Display::getInstance().setDigit(2, (FiFider::getEta()/600) % 6);
        Display::getInstance().setDigit(3, (FiFider::getEta()/60) % 10);
        Display::getInstance().setDigit(4, (FiFider::getEta()%2) * 0xFF);
    }else{
        Display::getInstance().setDigit(0, (FiFider::getEta()/600) % 6);
        Display::getInstance().setDigit(1, (FiFider::getEta()/60) % 10);
        Display::getInstance().setDigit(2, (FiFider::getEta()/10) % 6);
        Display::getInstance().setDigit(3, FiFider::getEta() % 10);
        Display::getInstance().setDigit(4, (FiFider::getEta()%2)*0xFF);
    }

    // Display::getInstance().setDigit(5, 0x1);
}

void FiFider::showInterval(void) {
    Display::getInstance().setDigit(0, (FiFider::getInterval()/36000) % 99);
    Display::getInstance().setDigit(1, (FiFider::getInterval()/3600) % 10);
    Display::getInstance().setDigit(2, (FiFider::getInterval()/600) % 6);
    Display::getInstance().setDigit(3, (FiFider::getInterval()/60) % 10);
    Display::getInstance().setDigit(4, 0);
    // Display::getInstance().setDigit(5, 0x2);
}

void FiFider::showPortion(void) {
    Display::getInstance().setDigit(0, 0);
    Display::getInstance().setDigit(1, (FiFider::getPortion()/100) % 10);
    Display::getInstance().setDigit(2, (FiFider::getPortion()/10) % 10);
    Display::getInstance().setDigit(3, FiFider::getPortion() % 10);
    Display::getInstance().setDigit(4, 1);
    // Display::getInstance().setDigit(5, 0x4);
}

void FiFider::cycleDisplayState(void) {
    if(_display_state == DST_ETA){
        _display_state = DST_INTERVAL;
    }else if(_display_state == DST_INTERVAL){
        _display_state = DST_PORTION;
    }
    else if(_display_state == DST_PORTION){
        _display_state = DST_ETA;
    }
}

void FiFider::increaseButton(void) {
    if(_is_holding){
        _is_holding = false;
    }else{
        if(_feeder_state != FST_WAITING) return;
        changeAmount(true);
        _ui_timestamp = millis();
    }
    _hold_init = 0;
}

void FiFider::holdIncreaseButton(void){
    _hold_init = millis();
    _is_holding = true;
    _hold_increase = true;
    changeAmount(_hold_increase);
    _ui_timestamp = millis();
    _hold_init = 0;
    _hold_down_count = HW_HOLD_INC_CNT;
}

void FiFider::decreaseButton(void) {
    if(_is_holding){
        _is_holding = false;
    }else{
        if(_feeder_state != FST_WAITING) return;
        changeAmount(false);
        _ui_timestamp = millis();
    }
    _hold_init = 0;
}

void FiFider::holdDecreaseButton(void){
    _hold_init = millis();
    _is_holding = true;
    _hold_increase = false;
    changeAmount(_hold_increase);
    _ui_timestamp = millis();
    _hold_init = 0;
    _hold_down_count = HW_HOLD_INC_CNT;
}

void FiFider::selectButton(void) {
    if(_feeder_state != FST_WAITING) return;
    cycleDisplayState();
    _ui_timestamp = millis();
    if(HW_SAVE_ON_SEL)
        FiFider::getInstance().saveState();
}

void FiFider::holdSelectButton(void) {
    if(_feeder_state != FST_WAITING) return;
    if(_display_state == DST_ETA){
        _eta = _interval;
        _ui_timestamp = millis();
        if(HW_SAVE_ON_RES)
            FiFider::getInstance().saveState();
    }else{
        selectButton();
    }

}

unsigned long FiFider::calculateStep(unsigned long value) {
    if(value >= 36000)
        return 3600;
    return 1800;
}

void FiFider::changeAmount(bool increase){
    unsigned long new_val;
    char mult = (2*(increase)-1);

    if(_display_state == DST_ETA) {
        new_val = FiFider::getInstance().getEta() + mult*60;
        FiFider::getInstance().setEta(new_val);
    }else if(_display_state == DST_INTERVAL) {
        unsigned long amount = FiFider::getInstance().calculateStep(FiFider::getInstance().getInterval());
        new_val = FiFider::getInstance().getInterval() + mult*amount;
        if(new_val >= HW_MIN_INTERVAL && new_val <= HW_MAX_INTERVAL){
            FiFider::getInstance().setInterval(new_val);
        }
    }else if(_display_state == DST_PORTION) {
        new_val = FiFider::getInstance().getPortion() + mult*1;
        if(new_val >= HW_MIN_PORTION && new_val <= HW_MAX_PORTION){
            FiFider::getInstance().setPortion(new_val);
        }
    }
}
