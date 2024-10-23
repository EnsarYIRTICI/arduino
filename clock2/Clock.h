#ifndef Clock_h
#define Clock_h
#include <LiquidCrystal_I2C.h>
#include "Arduino.h" 

class Clock {

  public:
    void setup();
    void start();
    void stop();
    void clock();
    void view();
    void raise();
    void decrease();
    
    bool showMode = false;
    int h = 12;
    int m = 0;

  private:
    void faint();
    void raiseCondition();
    void decreaseCondition();
    void dateAndTime();
    void mode();
    void zero(int value);

    int _millis;

    int prevTime = 0;
    int prevModeTime = 0;
    int btnPrevTime = 0;

    bool showFaint = false;

    int modeNum = 0;
 
    int s = 0;

    int y = 2023;
    int mn = 6;
    int d = 3;

};

#endif