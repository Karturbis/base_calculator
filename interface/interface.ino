// imports:
#include <math.h>
#include <LiquidCrystal.h>
#include <Keypad.h>


String key_input;
const String modes[4] = {"Menu", "Input base 1", "Input base 2", "Calculate"};
String mode;

// declare display pins
const int rs = 1;
const int en = 0;
const int data_0 = 8;
const int data_1 = 9;
const int data_2 = 10;
const int data_3 = 11;
const int data_4 = 5;
const int data_5 = 4;
const int data_6 = 3;
const int data_7 = 2;

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
  lcd.print("Base Number calculator!");
  menu();
}

void loop() {
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
      key_input = String(key_input + key);
    }
    lcd.setCursor(0, 1);
    lcd.print(key_input);
    delay(50);
 }

}

void menu() {
  mode = "menu";
  input();
  lcd.clear();
  lcd.print(key_input);
}