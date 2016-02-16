#include "FiFider.hpp"

FiFider::FiFider(){

}

void FiFider::begin(void){
    if(!Memory::getInstance().isReady()){
        setDefaultValues();
        Memory::getInstance().initialize();
    }
}


void FiFider::setDefaultValues(void){}
