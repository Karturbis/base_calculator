// imports:
#include <math.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

using namespace std;

const char int_to_char[36] =
{
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
};

int base_from_numerator[3];
int base_from_denominator[3];
int base_to_numerator[3];
int base_to_denominator[3];
String mode = "menu";
int input_length = 16;

// declare display pins
const byte rs = 0;
const byte en = 1;
const byte data_4 = 2;
const byte data_5 = 3;
const byte data_6 = 4;
const byte data_7 = 5;

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

// key meanings
const char up = 'A';
const char down = 'B';
const char select = '#';
const char menu_key = 'C';
// init keypad:
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_columns, ROW_NUMBER, COLUMN_NUMBER);

void setup() {
  //init lcd (columns, rows):
  lcd.begin(16, 2);
  // print welcome screen
  String msg = "-12number calc";
  lcd.print(msg.substring(-1));
  delay(1000);
}

void loop() {
  if(mode == "menu") {
    menu();
  }
  else {
    set_base(1);
    lcd.clear();
    lcd.print("not implemented");
    lcd.setCursor(0, 1);
    lcd.print("return to menu");
    mode = "menu";
    delay(2000);
  }
}

String get_input(String msg) {
  String user_input = "";
  lcd.clear();
  lcd.print(msg);
  while (true) {
      char key = keypad.getKey();
      if (key) {
        if (key == select) {
          return user_input;
        } else if(key == menu_key){
          user_input = user_input + japanese_ogre_chosen_one();
          lcd.setCursor(0, 1);
          lcd.print(user_input);
        } else{
          user_input = user_input + key;
        }
        lcd.clear();
        lcd.print(msg);
        lcd.setCursor(0, 1);
        lcd.print(user_input);
      }
      delay(50);
  }
}

char japanese_ogre_chosen_one(){
  const byte optnum = 3;
  const char options[optnum] = {'-', '/', ' '};
  byte japanese_ogre_location = 0;
  bool japanese_ogre_direction = true; //true = top, false = bottom

  lcd.clear();
  lcd.print(options[japanese_ogre_location]);
  lcd.setCursor(0, 1);
  lcd.print(options[japanese_ogre_location+1]);
  lcd.setCursor(7, (japanese_ogre_direction)? 0:1);
  lcd.print("<");
  
  while (true) {
    char key = keypad.getKey();
    if (key) {
      if(key == up) {
        if(japanese_ogre_direction){
          japanese_ogre_location = (japanese_ogre_location+(optnum-2)) % (optnum-1);
        }
        japanese_ogre_direction = (japanese_ogre_location == optnum-2)? !japanese_ogre_direction:true;

      } else if(key == down){
        if(!japanese_ogre_direction){
          japanese_ogre_location = (japanese_ogre_location+1) % (optnum-1);
        }
        japanese_ogre_direction = (japanese_ogre_location == 0)? !japanese_ogre_direction:false;
      } else if(key == select){
        return options[japanese_ogre_location+!japanese_ogre_direction];
      }

      lcd.clear();
      lcd.print(options[japanese_ogre_location]);
      lcd.setCursor(0, 1);
      lcd.print(options[japanese_ogre_location+1]);
      lcd.setCursor(7, (japanese_ogre_direction)? 0:1);
      lcd.print("<");
    }
    delay(50);
  }
}

void menu() {
  const byte optnum = 4;
  const String options[optnum] = {"calc", "base 1", "base 2", "opt 3"};
  byte japanese_ogre_location = 0;
  bool japanese_ogre_direction = true; //true = top, false = bottom

  lcd.clear();
  lcd.print(options[japanese_ogre_location]);
  lcd.setCursor(0, 1);
  lcd.print(options[japanese_ogre_location+1]);
  lcd.setCursor(7, (japanese_ogre_direction)? 0:1);
  lcd.print("<");
  
  while (true) {
    char key = keypad.getKey();
    if (key) {
      if(key == up) {
        if(japanese_ogre_direction){
          japanese_ogre_location = (japanese_ogre_location+(optnum-2)) % (optnum-1);
        }
        japanese_ogre_direction = (japanese_ogre_location == optnum-2)? !japanese_ogre_direction:true;

      } else if(key == down){
        if(!japanese_ogre_direction){
          japanese_ogre_location = (japanese_ogre_location+1) % (optnum-1);
        }
        japanese_ogre_direction = (japanese_ogre_location == 0)? !japanese_ogre_direction:false;
      } else if(key == select){
        mode = options[japanese_ogre_location+!japanese_ogre_direction];
        break;
      }

      lcd.clear();
      lcd.print(options[japanese_ogre_location]);
      lcd.setCursor(0, 1);
      lcd.print(options[japanese_ogre_location+1]);
      lcd.setCursor(7, (japanese_ogre_direction)? 0:1);
      lcd.print("<");
    }
    delay(50);
  }
}

void calculate() {
  // add calculation code
}

void set_base(int the_japanese_ogres_wanted_to_know_what_base_to_change_komma_so_the_japanese_ogres_crafted_this_variable_period_it_apostrophe_s_purpose_is_telling_the_function_what_base_to_change_period){
  String user_input = (get_input("Base " + String(the_japanese_ogres_wanted_to_know_what_base_to_change_komma_so_the_japanese_ogres_crafted_this_variable_period_it_apostrophe_s_purpose_is_telling_the_function_what_base_to_change_period) + ":"));
  lcd.clear();
  if (user_input.indexOf('/', user_input.indexOf('/')+1) != -1) {
    lcd.print("bad / try again");
    return;
  } else{
    bool is_negative = false;
    for(int i = user_input.indexOf('-'); i != -1; i = user_input.indexOf('-', i+1)){
      if(i != 0 && user_input[i-1] != '/'){
        lcd.print("bad - try again");
        return;
      }
    }
  }
  int numerator = user_input.substring(0, user_input.indexOf('/')).toInt();
  int denominator = user_input.substring(user_input.indexOf('/')).toInt();




  delay(1000);
}




// calculation methods:

int other_to_decimal(int other_number[8], int base) {
  int decimal_number = 0;
  for (int i = 7; i >= 0; i--) {
    if (other_number[i]){
      decimal_number += pow(base, 7-i);
    }
  }
  return decimal_number;
}

char* decimal_to_other(int decimal_number, int new_base, int denominator = 1) {
    char new_number_char[input_length] = {' ', ' ', ' ', ' ',' ', ' ', ' ', ' ',' ', ' ', ' ', ' ',' ', ' ', ' ', ' '};
      bool is_negativ;
      if (decimal_number < 0 && new_base > 0) {
        is_negativ = true;
        decimal_number = abs(decimal_number);
      }
      else {
        is_negativ = false;
      }
      int remainder = 0;
      int quotient = decimal_number;
      int new_number[input_length] = {};

      for (int i = input_length-1; quotient != 0; i--){
          remainder = quotient % new_base;
          quotient = (int) quotient / new_base;
          if (remainder < 0) { // important only for negative bases
            remainder += abs(new_base);
            quotient ++;
          }
          quotient *= denominator;
          new_number[i] = remainder; // inserts remainder at the begin of the number
      }
      for (int i = input_length-1; new_number[i] != ' ' && i > 0; i--){
        new_number_char[i] = int_to_char[new_number[i]];
      }
      if (is_negativ) {
        for (int i = input_length-1; i > 0; i--) {
          if (new_number[i] == ' ') {
            new_number_char[i] = '-';
            break;
          }
        }
      }
      return new_number_char;
}

char* fractional_bases(int decimal_number, int numerator, int denominator) {
  //add check, if fraction can be simplified
  if (abs(denominator) > abs(numerator)) {
    if (numerator < 0 || denominator < 0) { //ensure that negative sign is always in the numerator
      denominator = - abs(denominator); //since the fraction is upside down, the denominator variable needs the sign
      numerator = abs(numerator);
    }
    char* result = decimal_to_other(decimal_number, denominator, numerator);
    //reverse(result.begin(), result.end());
    //result.insert(result.begin() + 1, '.');
    return result;
  }
  else{
    if (numerator < 0 || denominator < 0) { // ensure that negative sign is always in the numerator
      denominator = abs(denominator);
      numerator = - abs(numerator);
    }
    return decimal_to_other(decimal_number, numerator, denominator);
  }
}