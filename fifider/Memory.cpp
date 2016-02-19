#include "Memory.hpp"
#include <EEPROM.h>
#include <string.h>
#include <Arduino.h>

Memory& Memory::getInstance(void){
    static Memory instance;
    return instance;
}

bool Memory::isReady(void) {
    char magic_string[HW_MAGSTR_LEN+1];
    readString(HW_MAGSTR_ADDR, HW_MAGSTR_ADDR+HW_MAGSTR_LEN, magic_string);
    magic_string[HW_MAGSTR_LEN] = 0;
    return strcmp(magic_string, HW_MAGSTR_VAL) == 0;
}

void Memory::initialize(void) {
    write(HW_MAGSTR_ADDR, HW_MAGSTR_VAL, HW_MAGSTR_LEN);
}

void Memory::write(unsigned int address, char* data, unsigned int length) {
    for(unsigned int i = 0; i < length && i+address < EEPROM.length(); i++){
        EEPROM.write(i+address, data[i]);
    }
}

void Memory::write(unsigned int address, unsigned long data, unsigned int length) {
    unsigned long power = pow(256,length-1)+1;

    for(unsigned int i = 0; i < length && i+address < EEPROM.length(); i++){
        unsigned char digit_data = (data/ (power) ) % 256;
        EEPROM.write(i+address, digit_data);
        power /= 256;
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
    unsigned long power = pow(256,end_address-start_address-1)+1;
    unsigned long data=0;

    for (mem_idx = start_address; mem_idx < end_address; mem_idx+=1) {
        unsigned char digit = EEPROM.read(mem_idx);
        data += digit * power;
        power /= 256;
    }

    return data;
}
