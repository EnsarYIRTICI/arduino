#include "Menu.h"
#include "Clock.h"
#include "Alarm.h"
#include "Stopwatch.h"
#include "Timer.h"

Menu m;
Clock c;
Alarm a;
Stopwatch stw;
Timer t;

int selectPrev = LOW;
int backPrev = LOW;
int upPrev = LOW;
int downPrev = LOW;

bool backEnable = true;

void setup() {
  
  t.setup();
  stw.setup();
  a.setup();
  c.setup();
  m.setup();

  for(int i = 2; i<6; i++)
  {
    pinMode(i,INPUT);
  }

  pinMode(13,OUTPUT);

  noInterrupts();         
  TCCR1A = 0;             
  TCCR1B = 0;            
  TCNT1  = 0;             
  OCR1A = 1999;          
  TCCR1B |= (1 << WGM12); 
  TCCR1B |= (1 << CS11);  
  TIMSK1 |= (1 << OCIE1A);
  interrupts(); 

}


void loop() {

  int down = digitalRead(2);
  int up = digitalRead(3);
  int select = digitalRead(4);
  int back = digitalRead(5);

  c.clock();
  t.timer();

  if(a.alarmActive == true)
  {
    if(a.h == c.h && a.m == c.m)
    { 
      digitalWrite(13,HIGH);
      backEnable = false; 
      if(back == LOW && backPrev == HIGH)
      {
        a.active();
        digitalWrite(13, LOW);
        backEnable = true;
      }
    }
  }

  if(backEnable == true)
  {
    if(back == LOW && backPrev == HIGH)
    {
      m.back();
    }
  }

  switch (m.menu) {

  case 1:

    c.view();

    if(select == LOW && selectPrev == HIGH)
    {
      backEnable = false;
      c.stop();
    }

    if(c.showMode == true)
    {
      
      if(down==HIGH)
      {
        c.raise();
      }

      if(up==HIGH)
      {
        c.decrease();
      }

      if(back == LOW && backPrev == HIGH)
      {
        backEnable=true;
        c.start();
      }

    }
    break;

  case 2:

    a.view();

    if(select == LOW && selectPrev == HIGH)
    {
      backEnable = false;
      a.regulation();
    }

    if(a.showMode == true)
    {

      if(down==HIGH)
      {
        a.raise();
      }

      if(up==HIGH)
      {
        a.decrease();
      }

      if(back == LOW && backPrev == HIGH)
      {
        backEnable=true;
        a.draft();
      }

    }
    else
    {
      if(down == LOW && downPrev == HIGH)
      {
        a.active();
      }
    }
    break;

  case 3:

    stw.view();

    if(select == LOW && selectPrev == HIGH)
    {
      stw.start();
    }
    if(up == LOW && upPrev == HIGH)
    {
      stw.reset();
    }
    break;

  case 4:

    t.view();

    if(select == LOW && selectPrev == HIGH)
    {     
      if(t.prevMode == true)
      {
        backEnable = false;
        t.regulation();
      }
    }

    if(t.showMode == true)
    {

      if(down==HIGH)
      {
        t.raise();
      }

      if(up==HIGH)
      {
        t.decrease();
      }

      if(back == LOW && backPrev == HIGH)
      {
        backEnable=true;
        t.draft();
      }

    }
    else
    {
      if(down == LOW && downPrev == HIGH)
      {
        t.active();
      }
      if(up == LOW && upPrev == HIGH)
      {
        t.reset();
      }
    }
    break;
    
  default:

    if(down == LOW && downPrev == HIGH)
    {
      m.scrollBottom();
    }

    if(up == LOW && upPrev == HIGH)
    {
      m.scrollTop();
    }

    if(select==LOW && selectPrev == HIGH)
    {
      m.select();
    }
    break;

  }

  selectPrev = select;
  backPrev = back;
  upPrev = up;
  downPrev = down;

}

ISR(TIMER1_COMPA_vect)
{   
  stw.stopwatch();
}



