#include "Arduino.h"
#include <LiquidCrystal_I2C.h>

class Calculator{

public:
	void calculator();
	void setup();

private:
	String number = "0";
	String value = "";
	String equalState = "none";
	String equalPrevState = "none";

	bool numState = false;

	float numberPrev = 0;
	float numberSuper = 0;

  int numinState = 1;
  String numinstr1 = "1";
  String numinstr2 = "2";

  int num2Prev = LOW;
  int num3Prev = LOW;
  int num4Prev = LOW;
  int num5Prev = LOW;

  int num7Prev = LOW;
  int num8Prev = LOW;
  int num9Prev = LOW;
  int num10Prev = LOW;
  int num11Prev = LOW;

	void equal();
	void press();
  void change(int key, int keyPrev);
  void numin(int key, int keyPrev, String strnum);
	void procces(int key, int keyPrev, String symbol);
	void enter(int key, int keyPrev);
	void back(int key, int keyPrev);

};
