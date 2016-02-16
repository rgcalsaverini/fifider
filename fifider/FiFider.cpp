#include "FiFider.hpp"
#include "TimerOne.h"

unsigned long FiFider::_eta = HW_DEF_INTERVAL;
unsigned long FiFider::_interval = HW_DEF_INTERVAL;
unsigned char FiFider::_portion = HW_DEF_PORTION;
FiFider::FeederState FiFider::_feeder_state = FST_WAITING;
FiFider::DisplayState FiFider::_display_state = DST_ETA;
unsigned long FiFider::_display_state_change = 0;

FiFider& FiFider::getInstance(void) {
    static FiFider instance;
    return instance;
}

void FiFider::begin(void) {
    if(!Memory::getInstance().isReady()) {
        _eta = HW_DEF_INTERVAL;
        _interval = HW_DEF_INTERVAL;
        _portion = HW_DEF_PORTION;
        _feeder_state = FST_WAITING;
        _display_state = DST_ETA;
        saveState();
        Memory::getInstance().initialize();
    }else{
        loadState();
    }

    Timer1.initialize(1000000);
    Timer1.attachInterrupt(FiFider::timerOverflow);

    _increase_btn.initialize(HW_BTN_INCR_PIN);
    _increase_btn.onUp(FiFider::increaseBtnCallback);

    _decrease_btn.initialize(HW_BTN_DECR_PIN);
    _decrease_btn.onUp(FiFider::decreaseBtnCallback);

    _select_btn.initialize(HW_BTN_SEL_PIN);
    _select_btn.onUp(FiFider::selectBtnCallback);


    Display::getInstance().initialize();
}


void FiFider::saveState(void) {
    Memory::getInstance().write(HW_ETA_ADDR, FiFider::getEta(), HW_ETA_BITS);
    Memory::getInstance().write(HW_INTERVAL_ADDR, FiFider::getInterval(), HW_INTERVAL_BITS);
    Memory::getInstance().write(HW_PORTION_ADDR, FiFider::getPortion(), HW_PORTION_BITS);
}

void FiFider::loadState(void) {
    FiFider::_eta = Memory::getInstance().readLong(HW_ETA_ADDR, HW_ETA_ADDR+HW_ETA_BITS);
    FiFider::_interval = Memory::getInstance().readLong(HW_INTERVAL_ADDR, HW_INTERVAL_ADDR+HW_INTERVAL_BITS);
    FiFider::_portion = Memory::getInstance().readLong(HW_PORTION_ADDR, HW_PORTION_ADDR+HW_PORTION_BITS);
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
    _increase_btn.check();
    _decrease_btn.check();
    _select_btn.check();

    if(_feeder_state == FST_WAITING) {
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

    if(_display_state != DST_ETA && millis() - _display_state_change > HW_DSP_TIMEOUT)
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

    Display::getInstance().setDigit(5, 0x1);
}

void FiFider::showInterval(void) {
    Display::getInstance().setDigit(0, (FiFider::getInterval()/36000) % 99);
    Display::getInstance().setDigit(1, (FiFider::getInterval()/3600) % 10);
    Display::getInstance().setDigit(2, (FiFider::getInterval()/600) % 6);
    Display::getInstance().setDigit(3, (FiFider::getInterval()/60) % 10);
    Display::getInstance().setDigit(4, 1);
    Display::getInstance().setDigit(5, 0x2);
}

void FiFider::showPortion(void) {
    Display::getInstance().setDigit(0, 0);
    Display::getInstance().setDigit(1, (FiFider::getPortion()/100) % 10);
    Display::getInstance().setDigit(2, (FiFider::getPortion()/10) % 10);
    Display::getInstance().setDigit(3, FiFider::getPortion() % 10);
    Display::getInstance().setDigit(4, 0);
    Display::getInstance().setDigit(5, 0x4);
}

void FiFider::cycleDisplayState(void) {
    if(_display_state == DST_ETA) _display_state = DST_INTERVAL;
    else if(_display_state == DST_INTERVAL) _display_state = DST_PORTION;
    else if(_display_state == DST_PORTION) _display_state = DST_ETA;
    _display_state_change = millis();
}

void FiFider::increaseBtnCallback(void) {
    unsigned int new_val;
    if(_display_state == DST_ETA) {
        new_val = FiFider::getInstance().getEta() + FiFider::getInstance().calculateStep(FiFider::getInstance().getEta());
        FiFider::getInstance().setEta(new_val);
    }else if(_display_state == DST_INTERVAL) {
        new_val = FiFider::getInstance().getInterval() + FiFider::getInstance().calculateStep(FiFider::getInstance().getInterval());
        FiFider::getInstance().setInterval(new_val);
    }else if(_display_state == DST_PORTION) {
        new_val = FiFider::getInstance().getPortion() + FiFider::getInstance().calculateStep(FiFider::getInstance().getPortion());
        FiFider::getInstance().setPortion(new_val);
    }
}
void FiFider::decreaseBtnCallback(void) {
    unsigned int new_val;
    if(_display_state == DST_ETA) {
        new_val = FiFider::getInstance().getEta() - FiFider::getInstance().calculateStep(FiFider::getInstance().getEta());
        FiFider::getInstance().setEta(new_val);
    }else if(_display_state == DST_INTERVAL) {
        new_val = FiFider::getInstance().getInterval() - FiFider::getInstance().calculateStep(FiFider::getInstance().getInterval());
        FiFider::getInstance().setInterval(new_val);
    }else if(_display_state == DST_PORTION) {
        new_val = FiFider::getInstance().getPortion() - FiFider::getInstance().calculateStep(FiFider::getInstance().getPortion());
        FiFider::getInstance().setPortion(new_val);
    }
}

void FiFider::selectBtnCallback(void) {
    cycleDisplayState();
}

unsigned int FiFider::calculateStep(unsigned int value) {
    if(value >= 21600)
        return 3600;
    else if(value >= 3600)
        return 1800;
    else if(value >= 1800)
        return 600;
    else if(value >= 300)
        return 300;
    return 60;
}
