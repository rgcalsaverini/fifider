#include "FiFider.hpp"
#include "TimerOne.h"

unsigned long FiFider::_eta = HW_DEF_INTERVAL;
unsigned long FiFider::_interval = HW_DEF_INTERVAL;
unsigned char FiFider::_portion = HW_DEF_PORTION;

FiFider& FiFider::getInstance(void){
    static FiFider instance;
    return instance;
}

void FiFider::begin(void){
    if(!Memory::getInstance().isReady()){
        _eta = HW_DEF_INTERVAL;
        _interval = HW_DEF_INTERVAL;
        _portion = HW_DEF_PORTION;
        saveState();
        Memory::getInstance().initialize();
    }else{
        loadState();
    }

    Timer1.initialize(1000000);
    Timer1.attachInterrupt(FiFider::timerOverflow);

    _increase_btn.initialize(HW_BTN_INCR_PIN);
    _decrease_btn.initialize(HW_BTN_DECR_PIN);
    _select_btn.initialize(HW_BTN_SEL_PIN);

    Display::getInstance().initialize();
}


void FiFider::saveState(void){
    Memory::getInstance().write(HW_ETA_ADDR, FiFider::getEta(), HW_ETA_BITS);
    Memory::getInstance().write(HW_INTERVAL_ADDR, FiFider::getInterval(), HW_INTERVAL_BITS);
    Memory::getInstance().write(HW_PORTION_ADDR, FiFider::getPortion(), HW_PORTION_BITS);
}

void FiFider::loadState(void){
    FiFider::_eta = Memory::getInstance().readLong(HW_ETA_ADDR, HW_ETA_ADDR+HW_ETA_BITS);
    FiFider::_interval = Memory::getInstance().readLong(HW_INTERVAL_ADDR, HW_INTERVAL_ADDR+HW_INTERVAL_BITS);
    FiFider::_portion = Memory::getInstance().readLong(HW_PORTION_ADDR, HW_PORTION_ADDR+HW_PORTION_BITS);
}

void FiFider::timerOverflow(void){
    FiFider::_eta -= 1;

    if(FiFider::_eta < 0)
        FiFider::getInstance().setEta(FiFider::getInstance().getInterval());

    if(FiFider::_eta%30 == 0)
        FiFider::getInstance().saveState();
}

void FiFider::checkState(void){
    //TODO Check buttons here

    if(_eta >= 3600){
        Display::getInstance().setDigit(0, (FiFider::getEta()/36000) % 99);
        Display::getInstance().setDigit(1, (FiFider::getEta()/3600) % 10);
        Display::getInstance().setDigit(2, (FiFider::getEta()/600) % 6);
        Display::getInstance().setDigit(3, (FiFider::getEta()/60) % 10);
        Display::getInstance().setDigit(4, (FiFider::getEta()%2)*0xFF);

    }else{
        Display::getInstance().setDigit(0, (FiFider::getEta()/600) % 6);
        Display::getInstance().setDigit(1, (FiFider::getEta()/60) % 10);
        Display::getInstance().setDigit(2, (FiFider::getEta()/10) % 6);
        Display::getInstance().setDigit(3, FiFider::getEta() % 10);
        Display::getInstance().setDigit(4, (FiFider::getEta()%2)*0xFF);
    }

    Display::getInstance().out();
}
