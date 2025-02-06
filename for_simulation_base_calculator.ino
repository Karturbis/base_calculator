// imports:
#include <math.h>
#include <vector>
#include <LiquidCrystal.h>
#include <Keypad.h>

/*
Analog pins have digital
names:
A0 => 14
A1 => 15
...
A5 => 19
*/
//declare button pins:
int button_0 = 19;
int button_1 = 18;
int button_enter = 17;
int switch_number = 16;
int switch_base = 15;

//declare display pins:
LiquidCrystal lcd_1(1, 0, 5, 4, 3, 2);

//keypad:
const int ROW_NUMBER = 4;
const int CLOUMN_NUMBER = 4;
char keys[ROW_NUMBER][CLOUMN_NUMBER] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUMBER] = {13, 12, 11, 10};
byte pin_columns[CLOUMN_NUMBER] = {9, 8, 7, 6};

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_columns, ROW_NUMBER, CLOUMN_NUMBER);

void setup()
{
  // init buttons:
  pinMode(button_0, INPUT);
  pinMode(button_1, INPUT);
  pinMode(button_enter, INPUT);
  pinMode(switch_number, INPUT);
  pinMode(switch_base, INPUT);
  //init lcd (columns, rows):
  lcd_1.begin(16, 2);
  // Print hello world
  lcd_1.print("hello world!");
}

void loop()
{
  mode_input_number();
  
}


int mode_input_number(int base) {
  bool inputing = true;
  vector<char> input = {};
    while (inputing) {
      input.push_back(keypad.getKey());
      if (input[input.end()] == '#') {
        inputing = false;
      }
      if (key_input) {
        lcd_1.clear();
        lcd_1.print(key_input);
      }
    delay(100);
}
}


int binary_to_decimal(int binary_number[8]) {
  int decimal_number = 0;
  for (int i = 7; i >= 0; i--) {
    if (binary_number[i]){
      decimal_number += pow(2, 7-i);
    }
  }
  return decimal_number;
}