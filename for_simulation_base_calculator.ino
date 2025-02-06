// imports:
#include <math.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
// declare led pins:
int led_0 = 6;
int led_1 = 7;
int led_2 = 8;
int led_3 = 9;
int led_4 = 10;
int led_5 = 11;
int led_6 = 12;
int led_7 = 13;
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

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_columns, ROW_NUMBER, CLOUMN_NUMBER);

void setup()
{
  // initialize leds:
  pinMode(led_0, OUTPUT);
  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  pinMode(led_4, OUTPUT);
  pinMode(led_5, OUTPUT);
  pinMode(led_6, OUTPUT);
  pinMode(led_7, OUTPUT);
 
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
  bool inputing = true;
  int enter_input = 0;
  int button_0_input = 0;
  int button_1_input = 0;
  int input_number[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  int input_counter = 0;
  char key_input;
  while (inputing) {
    button_0_input = digitalRead(button_0);
    button_1_input = digitalRead(button_1);
    key_input = keypad.getKey();
    if (button_0_input) {
      input_number[input_counter] = LOW;
      input_counter ++;
    }
    if (button_1_input) {
      input_number[input_counter] = HIGH;
      input_counter ++;
    }
    enter_input = digitalRead(button_enter);
    if (enter_input) {
      inputing = false;
    }
    if (input_counter == 8) {
      inputing = false;
    }
    digitalWrite(led_0, input_number[0]);
    digitalWrite(led_1, input_number[1]);
    digitalWrite(led_2, input_number[2]);
    digitalWrite(led_3, input_number[3]);
    digitalWrite(led_4, input_number[4]);
    digitalWrite(led_5, input_number[5]);
    digitalWrite(led_6, input_number[6]);
    digitalWrite(led_7, input_number[7]);
    if (key_input) {
      lcd_1.clear();
      lcd_1.print(key_input);
    }
    delay(100);
  }
}

int base_10(int base_2_number[8]) {
  int base_10_number = 0;
  for (int i = 7; i >= 0; i--) {
    if (base_2_number[i]){
      base_10_number += pow(2, 7-i);
    }
  }
  return base_10_number;
}