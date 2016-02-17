#include "FiFider.hpp"


void setup(){
    FiFider::getInstance().begin();
//    FiFider::getInstance()._eta = 28800;
}

void loop() {
//    FiFider::getInstance()._eta -= 10;
    FiFider::getInstance().checkState();
//    Display::getInstance().out();
}

//#include "Button.hpp"
//#include "Display.hpp"
//
//Button b;
//
//void down(void){Serial.println("DOWN");}
//
//void up(void){Serial.println("UP");}
//
//void hold(void){Serial.println("HOLD");}
//
//void setup(){
//  Serial.begin(9600);
//  b.initialize(8);
//  b.onDown(down);
//  b.onUp(up);
//  b.onHold(hold);
//  Display::getInstance().initialize();
//}
//
//void loop(){
//  b.check();
////  /* Forma 4 */
////  for(int i = 0 ; i < 10000 ; i++){
////    Display::getInstance().setDigit(0, i%10);
////    Display::getInstance().setDigit(1, (i/10)%10);
////    Display::getInstance().setDigit(2, (i/100)%10);
////    Display::getInstance().setDigit(3, (i/1000)%10);
////    Display::getInstance().digitOut(0);
////    Display::getInstance().digitOut(1);
////    Display::getInstance().digitOut(2);
////    Display::getInstance().digitOut(3);
////  }
//
//  /* Forma 4 */
//  for(int i = 0 ; i < 10000 ; i++){
//    Display::getInstance().setDigit(0, i%10);
//    Display::getInstance().setDigit(1, (i/10)%10);
//    Display::getInstance().setDigit(2, (i/100)%10);
//    Display::getInstance().setDigit(3, (i/1000)%10);
//    Display::getInstance().out();
//  }
////  Display::getInstance().out();
//}

