#ifndef TimeClass_h
#define TimeClass_h

#include "Arduino.h" 

class TimeClass{

  private:

    int h = 12;
    int m = 0;
    int s = 0;

    int y = 2023;
    int mn = 6;
    int d = 3;

    int clockOption = 1;

    void raiseCondition();
    void decreaseCondition();
    void zero(int value);

  public :

    void clear();
    void setup();
    void home();
    void clock();
    void mode();
    void raise();
    void decrease();
    void dateAndTime();
    void changeOption();

};

#endif




