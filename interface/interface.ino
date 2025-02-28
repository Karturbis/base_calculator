// imports:
#include <math.h>
#include <LiquidCrystal.h>
#include <Keypad.h>


String user_input;
int base_1[3];
int base_2[3];
const char modes[4] = {'m', '1', '2', 'c'};
char mode;

// declare display pins
const int rs = 0;
const int en = 1;
const int data_0 = 8;
const int data_1 = 9;
const int data_2 = 10;
const int data_3 = 11;
const int data_4 = 2;
const int data_5 = 3;
const int data_6 = 4;
const int data_7 = 5;

// init display pins:
LiquidCrystal lcd(rs, en, data_4, data_5, data_6, data_7);

// declare keypad pins:
const int ROW_NUMBER = 4;
const int COLUMN_NUMBER = 4;
char keys[ROW_NUMBER][COLUMN_NUMBER] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte pin_rows[ROW_NUMBER] = {13, 12, 11, 10};
byte pin_columns[COLUMN_NUMBER] = {9, 8, 7, 6};
// init keypad:
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_columns, ROW_NUMBER, COLUMN_NUMBER);

void setup() {
  //init lcd (columns, rows):
  lcd.begin(16, 2);
  // print welcome screen
  lcd.print("Base number calc");
  delay(1000);
  menu();
}

void loop() {
  switch (mode) {
    case 'm':
      menu();
      break;
    case '1':
      input_base_1();
      break;
    case '2':
      input_base_2();
      break;
    case 'c':
      calculate();
      break;
    default:
      menu();
      break;
  }
}

void input() {
 bool running = true;
 while (running) {
    lcd.clear();
    lcd.print(mode);
    char key = keypad.getKey();
    if (key) {
      if (key == '#') {
        break;
      }
      if (key == 'A') {
        lcd.clear();
        mode = "menu";
        user_input = "";
        break;
      }
      user_input = String(user_input + key);
    }
    lcd.setCursor(0, 1);
    lcd.print(user_input);
    delay(50);
 }

}

void menu() {
  mode = 'm';
  input();
  lcd.clear();
  lcd.print(user_input);
  mode = modes[user_input.toInt()];
}

void input_base_1() {
  mode = '1';
  input();

  //base_1 = {};

}

void input_base_2() {
  mode = '2';
  input();
  lcd.clear();
  lcd.print("Base 1 is:");
  lcd.setCursor(0, 1);
  lcd.print(user_input);
}

void calculate() {
  // add calculation code
}