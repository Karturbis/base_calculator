// imports:
#include <math.h>
#include <LiquidCrystal.h>
#include <Keypad.h>


using namespace std;

const char int_to_char[36] =
{
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
};

int base_1_numerator = 10;
int base_1_denominator = 1;
int base_2_numerator = 2;
int base_2_denominator = 1;

String mode = "menu";
const int input_length = 16;

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

//key meanings
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
  //lcd.print("Base number calc)";
  //delay(1000);
  int manum[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1};
  //lcd.print(other_to_decimal(manum, 2, 1));
  //char* ptr = fractional_bases(7, 2, -3);
  //char y = *ptr;
  // String a = "abcd";
  //lcd.print(other_to_decimal(false, &manum[0], 2, 1));
  //delay(1000);
  //lcd.clear();
}

 void loop() {
  if(mode == "menu") {
    menu();
  } else if(mode == "base 1"){
    set_base(1);
  } else if(mode == "base 2"){
    set_base(2);
  } else if(mode == "calc"){
    calculate();
  } else {
    lcd.clear();
    lcd.print("not implemented");
    lcd.setCursor(0, 1);
    lcd.print("return to menu");
    mode = "menu";
    delay(2000);
  }
 }

String get_input(String msg, String mode) {
  String user_input = "";
  lcd.clear();
  lcd.print(msg);
  while (true) {
      char key = keypad.getKey();
      if (key) {
        if (key == select) {
          return user_input;
        } else if(key == menu_key) {
          if (mode == "calculate") {
            //if (user_input.length() > 0) {
              int japanese_ogre_big_chungus = get_input("enter digit", "int only").toInt();
              if (japanese_ogre_big_chungus > 35) {
                lcd.setCursor(0, 1);
                lcd.print("too much chonk  ");
                delay(1000);
              } else {
                user_input = user_input + int_to_char[japanese_ogre_big_chungus];
              }
            // } else {
            //   user_input = user_input + '-';
            // }
          } else if (mode == "base") {
            user_input = user_input + japanese_ogre_chosen_one();
          }
          // lcd.setCursor(0, 1);
          // lcd.print(user_input);
        } else if (key >= '0' && key <= '9') {
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
  const byte optnum = 2;
  const char options[optnum] = {'/', '-'};
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
  const byte optnum = 3;
  const String options[optnum] = {"calc", "base 1", "base 2"};
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
  String user_input = get_input("enter b1 number", "calculate");
  lcd.clear();
  bool is_negative = (user_input[0] == '-');
  if (user_input.length()-is_negative < 0 || user_input.length()-is_negative > 16) {
    lcd.print("bad input");
    delay(1000);
    mode = "calc";
      return;
  }
  int user_input_array[input_length] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  for (int i = user_input.length()-1; i >= is_negative; i--) {
    user_input_array[input_length - user_input.length()+i] = ((int)user_input[i] <= '9')? (int)user_input[i] - (int)'0' : (int)user_input[i] - (int)'A' + 10;
  }

  //int user_inpt_array[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0};

  float decimal_number = other_to_decimal(is_negative, user_input_array, base_1_numerator, base_1_denominator);
  // lcd.print(decimal_number);
  // delay(100);
  // lcd.clear();
  String result = (decimal_number - round(decimal_number < 0.0001))? "":"R";
  result = result + japanese_ogre_transmutation_wizard(fractional_bases(round(decimal_number), base_2_numerator, base_2_denominator));
  //lcd.print(round(decimal_number));
  lcd.print(user_input);
  lcd.setCursor(0, 1);
  lcd.print(result);
  while (true) {
    char key = keypad.getKey();
    if (key == menu_key) {
      mode = "menu";
      return;
    }
    if (key == select) {
      mode = "calc";
      return;
    }
  }
}

void set_base(int the_japanese_ogres_wanted_to_know_what_base_to_change_komma_so_the_japanese_ogres_crafted_this_variable_period_it_apostrophe_s_purpose_is_telling_the_function_what_base_to_change_period){
  mode = "menu";
  String user_input = get_input("Base " + String(the_japanese_ogres_wanted_to_know_what_base_to_change_komma_so_the_japanese_ogres_crafted_this_variable_period_it_apostrophe_s_purpose_is_telling_the_function_what_base_to_change_period) + ":", "base");
  lcd.clear();
  if (user_input.indexOf('/', user_input.indexOf('/')+1) != -1) {
    lcd.print("bad / try again");
    delay(1000);
    return;
  } else{
    bool is_negative = false;
    for(int i = user_input.indexOf('-'); i != -1; i = user_input.indexOf('-', i+1)){
      if(i != 0 && user_input[i-1] != '/'){
        lcd.print("bad - try again");
        delay(1000);
        return;
      }
    }
  }

  int slash_index = user_input.indexOf('/');
  int numerator = user_input.substring(0, slash_index).toInt();
  int denominator = slash_index + 1? user_input.substring(slash_index + 1).toInt() : 1;
  if(!numerator || !denominator || numerator > 35 || denominator > 35 || numerator == denominator){
    lcd.print("input error");
    delay(1000);
    return;
  }

  if(the_japanese_ogres_wanted_to_know_what_base_to_change_komma_so_the_japanese_ogres_crafted_this_variable_period_it_apostrophe_s_purpose_is_telling_the_function_what_base_to_change_period == 1){
    base_1_numerator = numerator;
    base_1_denominator = denominator;
  } else{
    base_2_numerator = numerator;
    base_2_denominator = denominator;
  }
  
  
  
  lcd.clear();
  lcd.print(numerator);
  lcd.setCursor(0, 1);
  lcd.print(denominator);
  delay(1000);
}

// calculation methods:
float other_to_decimal(bool is_negative, int other_number[input_length], int numerator, int denominator) {
  float decimal_number = 0;
  for (int i = input_length-1; i >= 0; i--) { 
    decimal_number += other_number[i]*(pow(numerator, 15-i)/pow(denominator, 15-i));
  }
  return is_negative? -decimal_number : decimal_number;
  return decimal_number;
}

char* decimal_to_other(int decimal_number, int new_base, int denominator) {
  static char new_number_char[input_length];
  for (int i = 0; i < input_length; i++){
    new_number_char[i] = ' ';
  }
  if (!decimal_number){
    static char japnese_hidden_ogre[input_length] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '0'};
    return japnese_hidden_ogre;
  }
  bool is_negative;
  if (decimal_number < 0 && new_base > 0) {
    is_negative = true;
    decimal_number = abs(decimal_number);
  } else {
    is_negative = false;
  }
  int remainder = 0;
  int quotient = decimal_number;
  int new_number[input_length] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; //japanese ogres where to lazy to do it properly
  for (int i = input_length-1; quotient != 0; i--){
    if(i - is_negative < 0){
      static char japanese_fucking_ogre = '|';
      return &japanese_fucking_ogre;
    }
    remainder = quotient % new_base; 
    quotient = (int) quotient / new_base; //japanese ogre magic solution
    if (remainder < 0) { // important only for negative bases
      remainder += abs(new_base);
      quotient ++;
    }
    quotient *= denominator;
    new_number[i] = remainder; // inserts remainder at the begining of the number
  }
  for(int i = 0; i < input_length; i++){
    if(new_number[i] != -1){
      new_number_char[i] = int_to_char[new_number[i]];
    }
  }

  if (is_negative){
    for (int i = 0; i < input_length-1; i++) {
      if (new_number[i+1] != -1){
        new_number_char[i] = '-';
        break;
      }
    }
  }
  return new_number_char;
}

char* fractional_bases(int decimal_number, int numerator, int denominator) {
  //add check, if fraction can be simplified
  if (numerator < 0 && denominator < 0){
    numerator = abs(numerator);
    denominator = abs(denominator);
  }
  if (abs(denominator) > abs(numerator)) {
    if (numerator < 0 || denominator < 0) { //ensure that negative sign is always in the numerator
      denominator = -abs(denominator); //since the fraction is upside down, the denominator variable needs the sign
      numerator = abs(numerator);
    }
    char* flipped_result = decimal_to_other(decimal_number, denominator, numerator);
    if (*flipped_result != ' '){
      static char japanese_fucking_ogre = '|';
      return &japanese_fucking_ogre;
    }
    static char result[input_length];
    for (int i = 0; i < input_length; i++){
      result[i] = ' ';
    }
    int japanese_ogre_count = 0;
    for (int i = 0; i < input_length; i++){
      if (*(flipped_result+i) == ' '){
        result[i] = ' ';
        japanese_ogre_count++;
      } else {
        result[japanese_ogre_count + input_length -1 - i] = *(flipped_result+i);
      }
    }
    result[japanese_ogre_count-1] = result[japanese_ogre_count];
    result[japanese_ogre_count] = '.';
    return result;
  }
  else{
    if (numerator < 0 || denominator < 0) { // ensure that negative sign is always in the numerator
      denominator = abs(denominator);
      numerator = -abs(numerator);
    }
    return decimal_to_other(decimal_number, numerator, denominator);
  }
}

String japanese_ogre_transmutation_wizard(char* ogre_wizard_test_subject){
  if (*ogre_wizard_test_subject == '|'){
    return "subject escaped";
  }
  String transformed_japanese_ogre = "";
  for (int i = 0; i < input_length; i++){
    if (*(ogre_wizard_test_subject+i) != ' '){
      transformed_japanese_ogre = transformed_japanese_ogre + *(ogre_wizard_test_subject+i);
    }
  }
  return transformed_japanese_ogre;
}

//changed get_input
//added calculate
//added negative to other_to_decimal

//fix negative
//large inputs

//leading space for digits > 9
//remember to reset static









