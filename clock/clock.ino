#include "TimeClass.h"

TimeClass t;

int clockMenu = 1;

int menuPrev = LOW;
int optionPrev = LOW;

int currentTime;
int prevTime = 0;

int show = true;

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  
  t.setup(); 
}

void loop() {

  int menu = digitalRead(2);
  int option = digitalRead(3);
  int plus = digitalRead(4);
  int minus = digitalRead(5);

  currentTime = millis();

  if (menu == LOW && menuPrev == HIGH) {
    t.clear();
    clockMenu = clockMenu + 1;
    if(clockMenu == 3)
    {
      clockMenu = 1;
    }
  }

  if (clockMenu == 1) 
  {

    if(currentTime - prevTime >= 1000)
    {
      t.clock();
      prevTime = currentTime;
    }
    
  } 
  else if (clockMenu == 2)
  {

    if(currentTime - prevTime >= 250)
    {
      show = !show;
      prevTime = currentTime;
    }

    if(show)
    {
      t.mode();
    }
    else
    {
      t.dateAndTime();
    }
    
    if(plus == HIGH)
    {
      t.raise();
    }
  
    if(minus == HIGH)
    {
      t.decrease();
    }

    if(option == LOW && optionPrev == HIGH)
    {
      t.changeOption();
    }

  }

  optionPrev = option;
  menuPrev = menu;
}
