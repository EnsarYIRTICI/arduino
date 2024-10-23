#ifndef Alarm_h
#define Alarm_h
#include <LiquidCrystal_I2C.h>
#include "Arduino.h" 

class Alarm{

  public:
    void setup();
    void view();
    void draft();
    void regulation();
    void raise();
    void decrease();
    void active();

    bool showMode = false;
    bool alarmActive = false;

    int h = 5;
    int m = 0;

  private:
    void mode();
    void faint();
    void hourAndMin();
    void zero(int value);

    int _millis;

    int modeNum = 0;

    int btnPrevTime = 0;
    int prevTime = 0;

    bool showFaint = false;
   
    
};

#endif