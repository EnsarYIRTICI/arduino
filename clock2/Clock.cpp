#include "Clock.h"

static LiquidCrystal_I2C lcd(0x27,16,2);

void Clock::setup()
{
  lcd.backlight();
  lcd.init(); 
}

void Clock::start()
{
  modeNum = 0;
  showMode = false;
}

void Clock::stop()
{
  showMode = true;
  modeNum = modeNum+1;
  if(modeNum==7)
  {
    modeNum=1;
  }
}

void Clock::clock()
{
  _millis = millis ();

  if(showMode == false)
  {
    if(_millis - prevTime >= 1000)
    {
      s=s+1;
      raiseCondition();
      prevTime = _millis;
    }
  }
}


void Clock::view()
{
  if(showMode == false)
  {
    dateAndTime();
  }
  else
  {
    mode(); 
  }
}

void Clock::mode()
{
  if(_millis - prevModeTime >= 300)
  {
    showFaint = !showFaint;
    prevModeTime = _millis;
  }
  if(showFaint == true)
  {
    faint();
  }
  else
  {
    dateAndTime();
  }
}

void Clock::faint()
{
  if(modeNum == 1)  
  {
    lcd.setCursor(6,0);
    lcd.print("  ");
  }
  else if(modeNum == 2)
  {
    lcd.setCursor(3,0);
    lcd.print("  ");
  }
  else if(modeNum == 3)
  {
    lcd.setCursor(0,0);
    lcd.print("  ");
  }
  else if(modeNum == 4)
  {
    lcd.setCursor(8,1);
    lcd.print("  ");
  }
  else if(modeNum == 5)
  {
    lcd.setCursor(5,1);
    lcd.print("  ");
  }
  else if(modeNum == 6)
  {
    lcd.setCursor(0,1);
    lcd.print("    ");
  }
}

void Clock::raise()
{

  if(_millis - btnPrevTime >= 150)
  {
    if(modeNum == 1)
    {
      s=s+1;
    }
    else if(modeNum == 2)
    {
      m=m+1;
    }
    else if(modeNum == 3)
    {
      h=h+1;
    }
    else if(modeNum == 4)
    {
      d=d+1;
    }
    else if(modeNum == 5)
    {
      mn=mn+1;
    }
    else if(modeNum == 6)
    {
      y=y+1;
    }
    
    raiseCondition();
      
    btnPrevTime = _millis;
  }
  
  dateAndTime();

}

void Clock::decrease()
{

  if(_millis - btnPrevTime >= 150)
  {
    if(modeNum == 1)
    {
      s=s-1;
    }
    else if(modeNum == 2)
    {
      m=m-1;
    }
    else if(modeNum == 3)
    {
      h=h-1;
    }
    else if(modeNum == 4)
    {
      d=d-1;
    }
    else if(modeNum == 5)
    {
      mn=mn-1;
    }
    else if(modeNum == 6)
    {
      y=y-1;
    }

    decreaseCondition();
    
    btnPrevTime = _millis;
  }

  dateAndTime();

}



void Clock::zero(int value)
{
  if(value<10)
  {
    lcd.print(0);
  }
}

void Clock::dateAndTime()
{
  lcd.setCursor(0,0);

  zero(h);
  lcd.print(h);
  lcd.print(":");
  zero(m);
  lcd.print(m);
  lcd.print(":");
  zero(s);
  lcd.print(s);

  lcd.setCursor(0,1);

  lcd.print(y);
  lcd.print(":");
  zero(mn);
  lcd.print(mn);
  lcd.print(":");
  zero(d);
  lcd.print(d);
}

void Clock::raiseCondition()
{

  if(s==60){
    s=0;
    m=m+1;
  }
  if(m==60){
    m=0;
    h=h+1;
  }
  if(h==24){
    h=0;
    d=d+1;
  }

  if(mn==1|mn==3|mn==5|mn==7|mn==8|mn==10|mn==12)
  {
    if(d==32)
    {
    d=1;
    mn=mn+1;
    }

  }
  else if (mn==4|mn==6|mn==9|mn==11)
  {
    if(d==31)
    {
    d=1;
    mn=mn+1;
    }
  }
  else if (mn==2)
  { 
    if(y%4==0)
    {
      if(d==30)
      {
        d=1;
        mn=mn+1;
      }
    }
    else
    {
      if(d==29)
      {
        d=1;
        mn=mn+1;
      }
    }
  }

  if(mn==13){
    mn=1;
    y=y+1;
  }

}

void Clock::decreaseCondition()
{
  
  if(s==-1){
    s=59;
    m=m-1;
  }
  if(m==-1){
    m=59;
    h=h-1;
  }
  if(h==-1){
    h=23;
    d=d-1;
  }

  if(mn==1|mn==2|mn==4|mn==6|mn==8|mn==9|mn==11)
  {
    if(d==0)
    {
      d=31;
      mn=mn-1;
    }
  }
  else if (mn==5|mn==7|mn==10|mn==12)
  {
    if(d==0)
    {
      d=30;
      mn=mn-1;
    }
  }
  else if (mn==3)
  {
    if(y%4==0)
    {
      if(d==0)
      {
        d=29;
        mn=mn-1;
      }
    }
    else
    {
      if(d==0)
      {
        d=28;
        mn=mn-1;
      }
    }
  }

  if(mn==0){
    mn=12;
    y=y-1;
  }

}