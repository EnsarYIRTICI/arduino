#include "Menu.h"

static LiquidCrystal_I2C lcd(0x27,16,2);

String results[]={"Clock","Alarm","Stopwatch","Timer"};

int length = sizeof(results)/sizeof(String);

void Menu::setup()
{
  lcd.init();
  lcd.backlight(); 
  menuSetup();
  setMenuCursor(1,0);
}

void Menu::select()
{
  lcd.clear();
  if(cursor)
  {
    menu = position+1;
  }
  else
  {
    menu = position+2;
  }
}

void Menu::back()
{
  menu=0;
  position=0;
  cursor=true;
  menuSetup();
  setMenuCursor(1,0);
}

void Menu::emptyMenu()
{
  lcd.setCursor(0, 0);
  lcd.print("Empty Menu");
}

void Menu::setMenuCursor(int x, int y)
{
  lcd.setCursor(0,x);
  lcd.print(" ");
  lcd.setCursor(0,y);
  lcd.print("-");
}

void Menu::menuSetup()
{
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print(results[position]);
  lcd.setCursor(1,1);
  lcd.print(results[position+1]);
}

void Menu::menuEnd()
{
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print(results[length-1]);
  lcd.setCursor(1,1);
  lcd.print(results[0]);
}

void Menu::scrollBottom ()
{

  if(cursor)
  {
    setMenuCursor(0,1);
    cursor = !cursor;
    if(position>=length-1)
    {
      position=-1;
    }
  }
  else
  {
    position=position+1;
    if(position==length-1)
    {
      position=-1;
      menuEnd();
    }
    else if(position>=length-1)
    {
      position=0;
      menuSetup();
    }
    else
    {
      menuSetup();
    }
    setMenuCursor(0,1);
  }
}


void Menu::scrollTop()
{
  if(cursor)
  {
    position=position-1;
    if(position==-1)
    {
      position=length-1;
      menuEnd();
    }
    else if(position<=-1)
    {
      position=length-2;
      menuSetup();
    }
    else
    {
      menuSetup();
    }
    setMenuCursor(1,0);
  }
  else
  {
    setMenuCursor(1,0);
    cursor = !cursor;
    if(position<=-1)
    {
      position=length-1;
    }
  }
}
