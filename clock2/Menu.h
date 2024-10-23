#ifndef Menu_h
#define Menu_h
#include <LiquidCrystal_I2C.h>

class Menu{

  public:
    void setup();
    void select();
    void scrollTop();
    void scrollBottom();
    void back();
    void emptyMenu();

    int menu = 0;

  private:
    void setMenuCursor(int x,int y);
    void menuEnd();
    void menuSetup();

    int position = 0;

    bool cursor = true;

};

#endif