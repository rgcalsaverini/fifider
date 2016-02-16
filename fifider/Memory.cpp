#include "Memory.hpp"
#include <EEPROM.h>
#include <string.h>

Memory& Memory::getInstance(void){
    static Memory instance;
    return instance;
}

bool Memory::isReady(void) {
    char magic_string[MAGSTR_LEN+1];
    readString(MAGSTR_ADDR, MAGSTR_ADDR+MAGSTR_LEN, magic_string);
    magic_string[MAGSTR_LEN] = 0;
    return strcmp(magic_string, MAGSTR_VAL) == 0;
}

void Memory::initialize(void) {
    write(MAGSTR_ADDR, MAGSTR_VAL, MAGSTR_LEN);
}

void Memory::write(unsigned int address, char* data, unsigned int length) {
    for(unsigned int i = 0; i < length && i+address < EEPROM.length(); i++){
        EEPROM.write(i+address, data[i]);
    }
}

void Memory::readString(unsigned int start_address, unsigned int end_address, char* data) {
    unsigned int mem_idx, data_idx=0;

    for (mem_idx = start_address; mem_idx <= end_address; mem_idx+=1) {
        data[data_idx] = EEPROM.read(mem_idx);
        data_idx++;
    }
}

unsigned long Memory::readLong(unsigned int start_address, unsigned int end_address) {
    unsigned int mem_idx;
    unsigned long power=1, data=0;

    for (mem_idx = start_address; mem_idx <= end_address; mem_idx+=1) {
        data += EEPROM.read(mem_idx) * power;
        power *= 256;
    }

    return data;
}
