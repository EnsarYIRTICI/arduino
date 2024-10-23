#ifndef Stopwatch_h
#define Stopwatch_h
#include <LiquidCrystal_I2C.h>

class Stopwatch{
  
  public:
    void setup();
    void view();
    void start();
    void reset();
    void stopwatch();
    
  private:
    bool stwMode = false;

    int mm=0;
    int ss=0;
    int ms=0; 

};

#endif