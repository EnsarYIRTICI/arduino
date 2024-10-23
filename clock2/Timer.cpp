#include "Timer.h"

static LiquidCrystal_I2C lcd(0x27,16,2);

void Timer::setup()
{
  lcd.backlight();
  lcd.init(); 
}

void Timer::timer()
{
  _millis = millis();

  if(timerActive == true)
  {
    if(_millis - prevTime >= 1000)
    {
      if(h==0&&m==0&&s==0)
      {
        digitalWrite(13,OUTPUT);
      }
      else
      {
        s=s-1;
        decreaseCondition();
        prevTime = _millis;
      }
    }
  }
}

void Timer::reset()
{
  timerActive = false;
  prevMode = true;
  digitalWrite(13,LOW); 
}

void Timer::active()
{
  if(prevMode == true)
  {
    prevMode = false;
    h=hPrev;
    m=mPrev;
    s=sPrev;
  }
  timerActive = !timerActive;
}

void Timer::draft()
{
  showMode=false;
  modeNum=0;
}

void Timer::regulation()
{
  timerActive = false;
  showMode = true;
  modeNum = modeNum + 1;
  if(modeNum == 4)
  {
    modeNum = 1;
  }
}

void Timer::view()
{
  if(showMode == false)
  {
    if(prevMode == true)
    {
      prevView();
    }
    else
    {
      hourMinSec();
    }
  }
  else
  {
    mode();
  }
}

void Timer::mode()
{
  if(_millis - prevModeTime >= 300)
  {
    showFaint = !showFaint;
    prevModeTime = _millis;
  }
  if(showFaint == false)
  {
    prevView();
  }
  else
  {
    faint();
  }
}

void Timer::faint()
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
}

void Timer::prevView()
{
  lcd.setCursor(0,0);
  zero(hPrev);
  lcd.print(hPrev);
  lcd.print(":");
  zero(mPrev);
  lcd.print(mPrev);
  lcd.print(":");
  zero(sPrev);
  lcd.print(sPrev);
}

void Timer::hourMinSec()
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
}

void Timer::zero(int value)
{
  if(value<10)
  {
    lcd.print(0);
  }
}


void Timer::raise()
{

  if(_millis - btnPrevTime >= 150)
  {
    if(modeNum == 1)
    {
      sPrev=sPrev+1;
    }
    else if(modeNum == 2)
    {
      mPrev=mPrev+1;
    }
    else if(modeNum == 3)
    {
      hPrev=hPrev+1;
    }

    if(sPrev==60)
    {
      mPrev=mPrev+1;
      sPrev=0;
    }

    if(mPrev==60)
    {
      hPrev=hPrev+1;
      mPrev=0;
    }

    if(hPrev==24)
    {
      hPrev=0;
    }

    btnPrevTime = _millis;
    
  }

  prevView();

}

void Timer::decrease()
{

  if(_millis - btnPrevTime >= 150)
  {
    if(modeNum == 1)
    {
      sPrev=sPrev-1;
    }
    else if(modeNum == 2)
    {
      mPrev=mPrev-1;
    }
    else if(modeNum == 3)
    {
      hPrev=hPrev-1;
    }

    if(sPrev==-1)
    {
      mPrev=mPrev-1;
      sPrev=59;
    }

    if(mPrev==-1)
    {
      hPrev=hPrev-1;
      mPrev=59;
    }

    if(hPrev==-1)
    {
      hPrev=23;
    }

    btnPrevTime = _millis;

  }

  prevView();
  
}

void Timer::decreaseCondition()
{

  if(s==-1)
  {
    m=m-1;
    s=59;
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

}
