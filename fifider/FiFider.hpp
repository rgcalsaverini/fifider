#ifndef FIFIDER_FIFIDER_HPP
#define FIFIDER_FIFIDER_HPP

#include <Servo.h>
#include "TimerOne.h"

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

        enum ServoState{
            SST_IDLE = 0,
            SST_POS_1 = 1,
            SST_POS_2 = 2,
            SST_POS_3 = 3
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

        void feed(void);

        void saveState(void);
        void loadState(void);

        void showEta(void);
        void showInterval(void);
        void showPortion(void);

        static void timerOverflow(void);

        static void cycleDisplayState(void);

        static void increaseBtnCallback(void);
        static void decreaseBtnCallback(void);
        static void selectBtnCallback(void);
        static void resetEtaBtnCallback(void);

        static unsigned long calculateStep(unsigned long value);

    // private:
        static FeederState _feeder_state;
        static DisplayState _display_state;
        static ServoState _servo_state;
        static unsigned long _ui_timestamp;
        static unsigned long _servo_state_change;
        Button _increase_btn;
        Button _decrease_btn;
        Button _select_btn;
        static unsigned long _eta;
        static unsigned long _interval;
        static unsigned char _portion;
        Servo _servo;
};

#endif //FIFIDER_FIFIDER_HPP
