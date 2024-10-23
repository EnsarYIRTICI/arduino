#include "Calculator.h"

LiquidCrystal_I2C lcd(0x27,16,2);

void Calculator::calculator()
{
    int num2 = digitalRead(2);
    int num3 = digitalRead(3);
    int num4 = digitalRead(4);
    int num5 = digitalRead(5);

    int num7 = digitalRead(7);
    int num8 = digitalRead(8);
    int num9 = digitalRead(9);
    int num10 = digitalRead(10);
    int num11 = digitalRead(11);

    change(num9,num9Prev);
    numin(num10,num10Prev, numinstr1);
    numin(num11,num11Prev, numinstr2);

    procces(num2,num2Prev, "+");
    procces(num3,num3Prev, "-");
    procces(num4,num4Prev, "*");
    procces(num5,num5Prev, "/");

    enter(num7,num7Prev);
    back(num8,num8Prev);

    num2Prev = num2;
    num3Prev = num3;
    num4Prev = num4;
    num5Prev = num5;

    num7Prev = num7;
    num8Prev = num8;
    num9Prev = num9;
    num10Prev = num10;
    num11Prev = num11;
}

void Calculator::setup()
{
    lcd.init();
    lcd.backlight();

    for(int i = 2; i<12; i++)
    {
      pinMode(i,INPUT);
    }

    lcd.setCursor(0,0);
    lcd.print(number);
}

void Calculator::enter(int key, int keyPrev)
{
    if (key == LOW && keyPrev == HIGH)
    {
        equal();
    }
}

void Calculator::back(int key, int keyPrev)
{
    if (key == LOW && keyPrev == HIGH)
    {
        lcd.clear();

        number = "0";
        value = "";

        numberPrev = 0;
        numberSuper = 0;

        equalState = "none";
        equalPrevState = "none";

        numState = false;

        lcd.print(number);
    }
}

void Calculator::equal()
{

    lcd.clear();

    if (equalPrevState == "+")
    {
        numberPrev = (numberPrev + numberSuper);
    }
    else if (equalPrevState == "-")
    {
        numberPrev = (numberPrev - numberSuper);
    }
    else if (equalPrevState == "*")
    {
        numberPrev = (numberPrev * numberSuper);
    }
    else if (equalPrevState == "/")
    {
        numberPrev = (numberPrev / numberSuper);
    }


    if (numberPrev - (int)numberPrev == 0) 
    {
        number = String((int)numberPrev);
    }
    else 
    {
        number = String(numberPrev);
    }

    lcd.print(number);

    equalState = "none";
    numState = true;

}


void Calculator::procces(int key, int keyPrev, String symbol)
{
    if (key == LOW && keyPrev == HIGH)
    {
        if (equalState != "none" && numState == false)
        {
            equal();   
        }

        numberPrev = number.toInt();
        equalState = symbol;
        equalPrevState = symbol;
        numState = true;
    }
}

void Calculator::press()
{
    if (numState == true)
    {
        lcd.clear();
        number = "0";
        numState = false;
    }

    if (number == "0")
    {
        number = value;
    }
    else
    {
        number = number + value;
    }

    numberSuper = number.toInt();

    lcd.clear();

    lcd.print(number);
}


void Calculator::numin(int key, int keyPrev, String strnum)
{
    if (key == LOW && keyPrev == HIGH)
    {
        value = strnum;
        press();
    }
}

void Calculator::change(int key, int keyPrev)
{
  if (key == LOW && keyPrev == HIGH)
  {
    numinState = numinState + 1;
    if(numinState == 6)
    {
      numinState = 1;
    }

    switch (numinState) {
      case 1:
        numinstr1 = "1";
        numinstr2 = "2";
        break;
      case 2:
        numinstr1 = "3";
        numinstr2 = "4";
        break;
      case 3:
        numinstr1 = "5";
        numinstr2 = "6";  
        break;
      case 4:
        numinstr1 = "7";
        numinstr2 = "8";
        break;
      case 5:
        numinstr1 = "9";
        numinstr2 = "0";
        break;
    } 
  }
}


