#ifndef Timer_h
#define Timer_h
#include <LiquidCrystal_I2C.h>
#include "Arduino.h" 

class Timer{

  public:
    void setup();
    void timer();
    void view();
    void reset();
    void active();
    void raise();
    void decrease();
    void draft();
    void regulation();

    bool showMode = false;
    bool prevMode = true;

  private:
    void zero(int value);
    void mode();
    void prevView();
    void faint();
    void hourMinSec();
    void decreaseCondition();

    int _millis;

    int modeNum = 0;
   
    bool timerActive = false;
    bool showFaint = false;

    int prevTime = 0;
    int prevModeTime = 0;
    int btnPrevTime = 0;

    int hPrev = 0;
    int mPrev = 0;
    int sPrev = 5;

    int h = 0;
    int m = 0;
    int s = 0;

};

#endif