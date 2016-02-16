#ifndef FIFIDER_FIFIDER_HPP
#define FIFIDER_FIFIDER_HPP

#include "TimerOne.h"

#include "Memory.hpp"
#include "Button.hpp"
#include "hardware.hpp"
#include "Display.hpp"

#define MAGSTR_VAL    "fidev_1"
#define MAGSTR_LEN    7
#define MAGSTR_ADDR   113

class FiFider{
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

        static void timerOverflow(void);

    private:
        Button _increase_btn;
        Button _decrease_btn;
        Button _select_btn;
        static unsigned long _eta;
        static unsigned long _interval;
        static unsigned char _portion;
};

#endif //FIFIDER_FIFIDER_HPP
