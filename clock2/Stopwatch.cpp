#include "Stopwatch.h"

static LiquidCrystal_I2C lcd(0x27,16,2);

void Stopwatch::setup()
{
  lcd.backlight();
  lcd.init(); 
}

void Stopwatch::start()
{
  stwMode = !stwMode;
}
 
void Stopwatch::reset()
{
  stwMode = false;
  ms=0; 
  ss=0;
  mm=0;
}

void Stopwatch::view()
{
  lcd.setCursor(0,0);

  lcd.print((mm/10)%10);
  lcd.print(mm%10);
  lcd.print(":");
  lcd.print((ss/10)%10);
  lcd.print(ss%10);
  lcd.print(":");
  lcd.print((ms/100)%10);
  lcd.print((ms/10)%10);
}

void Stopwatch::stopwatch()
{
  if(stwMode == true)
  {
    ms=ms+1;
    if(ms>999)
    {
      ms=0;ss=ss+1;
      if(ss>59)
      {
        ss=0; 
        mm=mm+1;
      }
      if(mm>59)
      {
        mm=0;
      }
    } 
  }
}
