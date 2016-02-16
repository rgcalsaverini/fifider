#ifndef FIFIDER_FIFIDER_HPP
#define FIFIDER_FIFIDER_HPP

#include "Memory.hpp"

#define MAGSTR_VAL    "fidev_1"
#define MAGSTR_LEN    7
#define MAGSTR_ADDR   113

class FiFider{
    public:
        FiFider();
        void begin(void);

    private:
        void setDefaultValues(void);
};

#endif //FIFIDER_FIFIDER_HPP
