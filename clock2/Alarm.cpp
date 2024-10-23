#include "Alarm.h"

static LiquidCrystal_I2C lcd(0x27,16,2);

void Alarm::setup()
{
  lcd.backlight();
  lcd.init(); 
}

void Alarm::active()
{
  lcd.clear();
  alarmActive = !alarmActive;
}

void Alarm::draft()
{
  showMode=false;
  modeNum=0;
}

void Alarm::regulation()
{
  alarmActive = false;
  showMode = true;
  modeNum = modeNum + 1;
  if(modeNum == 3)
  {
    modeNum = 1;
  }
}

void Alarm::view()
{
  if(showMode == false)
  {
    hourAndMin();
  }
  else
  {
    mode();
  }
}

void Alarm::mode()
{
  _millis = millis();

  if(_millis - prevTime >= 300)
  {
    showFaint = !showFaint;
    prevTime = _millis;
  }
  if(showFaint==true)
  {
    faint();
  }
  if(showFaint==false)
  {
    hourAndMin();
  }
}

void Alarm::faint()
{
  if(modeNum == 1)  
  {
    lcd.setCursor(3,0);
    lcd.print("  ");
  }
  else if(modeNum == 2)
  {
    lcd.setCursor(0,0);
    lcd.print("  ");
  }
}

void Alarm::hourAndMin()
{
  lcd.setCursor(0,0);
  zero(h);
  lcd.print(h);
  lcd.print(":");
  zero(m);
  lcd.print(m);
  lcd.print(" ");
  lcd.print(alarmActive==true?"ON":"OFF");
}

void Alarm::zero(int value)
{
  if(value<10)
  {
    lcd.print(0);
  }
}

void Alarm::raise()
{

  _millis = millis();

  if(_millis - btnPrevTime >= 150)
  {
    if(modeNum == 1)
    {
      m=m+1;
    }
    else if(modeNum == 2)
    {
      h=h+1;
    }

    if(m==60)
    {
      h=h+1;
      m=0;
    }

    if(h==24)
    {
      h=0;
    }
    
    btnPrevTime = _millis;
  }

  hourAndMin();

}

void Alarm::decrease()
{

  _millis = millis();

  if(_millis - btnPrevTime >= 150)
  {  
    if(modeNum == 1)
    {
      m=m-1;
    }
    else if(modeNum == 2)
    {
      h=h-1;
    }

    if(m==-1)
    {
      h=h-1;
      m=59;
    }

    if(h==-1)
    {
      h=23;
    }
    
    btnPrevTime = _millis;
  }

  hourAndMin();

}