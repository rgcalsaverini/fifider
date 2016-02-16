#ifndef FIFIDER_MEMORY_HPP
#define FIFIDER_MEMORY_HPP

#include "hardware.hpp"

class Memory{
    public:
        static Memory& getInstance(void);

        Memory(Memory const&);
        void operator=(Memory const&);

        bool isReady(void);
        void initialize(void);

        void readString(unsigned int start_address, unsigned int end_address, char* data);
        unsigned long readLong(unsigned int start_address, unsigned int end_address);

        void write(unsigned int address, char* data, unsigned int length);
        void write(unsigned int address, unsigned long data, unsigned int length);

        private:
            Memory() {};
};

#endif //FIFIDER_MEMORY_HPP
