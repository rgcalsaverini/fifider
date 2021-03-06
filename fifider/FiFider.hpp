#ifndef FIFIDER_FIFIDER_HPP
#define FIFIDER_FIFIDER_HPP

#include <Arduino.h>

#include "Memory.hpp"
#include "Button.hpp"
#include "hardware.hpp"
#include "Display.hpp"

class FiFider{
    public:
        enum FeederState{
            FST_WAITING = 0,
            FST_FEEDING = 1
        };

        enum DisplayState{
            DST_ETA = 0,
            DST_INTERVAL = 1,
            DST_PORTION = 2
        };

    public:
        static FiFider& getInstance(void);

        void begin(void);

        void checkState(void);

        unsigned long getEta(void){return _eta;}
        void setEta(unsigned long val){_eta = val;}

        unsigned long getInterval(void){return _interval;}
        void setInterval(unsigned long val){_interval = val;}

        unsigned char getPortion(void){return _portion;}
        void setPortion(unsigned char val){_portion = val;}

    private:
        FiFider(FiFider const&);
        void operator=(FiFider const&);

        FiFider(){};

        void saveState(void);
        void loadState(void);

        void showEta(void);
        void showInterval(void);
        void showPortion(void);

        static void timerOverflow(void);

        static void cycleDisplayState(void);

        static void increaseButton(void);
        static void holdIncreaseButton(void);
        static void decreaseButton(void);
        static void holdDecreaseButton(void);
        static void selectButton(void);
        static void holdSelectButton(void);
        static void changeAmount(bool increase);


        static unsigned long calculateStep(unsigned long value);

    private:
        static FeederState _feeder_state;
        static DisplayState _display_state;
        static unsigned long _ui_timestamp;
        static unsigned long _hold_init;
        static bool _is_holding;
        static bool _hold_increase;
        static unsigned int _hold_down_count;
        Button _increase_btn;
        Button _decrease_btn;
        Button _select_btn;
        static unsigned long _eta;
        static unsigned long _interval;
        static unsigned char _portion;
};

#endif //FIFIDER_FIFIDER_HPP
