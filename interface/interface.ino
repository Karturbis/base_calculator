// Include necessary libraries
#include <math.h>          // For mathematical functions like pow()
#include <LiquidCrystal.h> // For controlling the LCD display
#include <Keypad.h>        // For interfacing with the keypad

using namespace std;       // Use the standard namespace

// Array to map integers (0-35) to their corresponding characters (0-9, A-Z)
const char int_to_char[36] = {
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 
  'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 
  'W', 'X', 'Y', 'Z'
};

// Variables to store the numerator and denominator for base 1 and base 2
int base_1_numerator = 10;
int base_1_denominator = 1;
int base_2_numerator = 2;
int base_2_denominator = 1;

// Current mode of the program (e.g., "menu", "base 1", "base 2", "calc")
String mode = "menu";

// Maximum length of input
const int input_length = 16;

// Pin definitions for the LCD display
const byte rs = 0;    // Register select pin
const byte en = 1;    // Enable pin
const byte data_4 = 2; // Data pin 4
const byte data_5 = 3; // Data pin 5
const byte data_6 = 4; // Data pin 6
const byte data_7 = 5; // Data pin 7

// Initialize the LCD display with the specified pins
LiquidCrystal lcd(rs, en, data_4, data_5, data_6, data_7);

// Keypad configuration
const int ROW_NUMBER = 4;    // Number of rows in the keypad
const int COLUMN_NUMBER = 4; // Number of columns in the keypad

// Keypad layout
char keys[ROW_NUMBER][COLUMN_NUMBER] = {
  {'M', 'U', 'D', 'S'}, // Row 1
  {'9', '6', '3', '*'}, // Row 2
  {'8', '5', '2', 'C'}, // Row 3
  {'7', '4', '1', '0'}  // Row 4
};

// Pin definitions for keypad rows and columns
byte pin_rows[ROW_NUMBER] = {13, 12, 11, 10};    // Row pins
byte pin_columns[COLUMN_NUMBER] = {9, 8, 7, 6}; // Column pins

// Keypad button meanings
const char up = 'U';       // Up button
const char down = 'D';     // Down button
const char select = 'S';   // Select button
const char menu_key = 'M'; // Menu button
const char special_char = 'C';
// Initialize the keypad
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_columns, ROW_NUMBER, COLUMN_NUMBER);

// Setup function: Runs once at startup
void setup() {
  // Initialize the LCD display with 16 columns and 2 rows
  lcd.begin(16, 2);
}

// Main loop: Continuously runs after setup
void loop() {
  // Handle different modes
  if (mode == "menu") {
    menu(); // Show the menu
  } else if (mode == "base 1") {
    set_base(1); // Set base 1
  } else if (mode == "base 2") {
    set_base(2); // Set base 2
  } else if (mode == "calc") {
    calculate(); // Perform calculations
  } else {
    // Handle unknown mode
    lcd.clear();
    lcd.print("not implemented");
    lcd.setCursor(0, 1);
    lcd.print("return to menu");
    mode = "menu";
    delay(2000);
  }
}

// Function to get user input from the keypad
String get_input(String msg, String mode) {
  String user_input = ""; // Store user input
  lcd.clear();
  lcd.print(msg); // Display the message on the LCD

  while (true) {
    char key = keypad.getKey(); // Get the pressed key
    if (key) {
      if (key == select) {
        return user_input; // Return the input when select is pressed
      } else if (key == menu_key) {
        if (mode == "calculate") {
          // Handle special input for calculation mode
          int japanese_ogre_big_chungus = get_input("enter digit", "int only").toInt();
          if (japanese_ogre_big_chungus > 35) {
            lcd.setCursor(0, 1);
            lcd.print("too much chonk  ");
            delay(1000);
          } else {
            user_input = user_input + int_to_char[japanese_ogre_big_chungus];
          }
        } 
      } else if (key == special_char) {
        if (mode == "base") {
          // Handle special input for base mode
          if (user_input.length() > 0) {
            user_input = user_input + '/'; 
          } else {
            user_input = user_input + '-';
          }
        } else if (mode == "calculate" && user_input.length() == 0) {
          user_input = user_input + '-';
        }

      } else if (key >= '0' && key <= '9') {
        // Append numeric keys to the input
        user_input = user_input + key;
      }
      // Update the LCD display
      lcd.clear();
      lcd.print(msg);
      lcd.setCursor(0, 1);
      lcd.print(user_input);
    }
    delay(50);
  }
}

// Function to display and navigate the menu
void menu() {
  const byte optnum = 3; // Number of menu options
  const String options[optnum] = {"calc", "base 1", "base 2"}; // Menu options
  byte japanese_ogre_location = 0; // Current menu selection
  bool japanese_ogre_direction = true; // Direction of selection (true = top, false = bottom)

  // Display the menu
  lcd.clear();
  lcd.print(options[japanese_ogre_location]);
  lcd.setCursor(0, 1);
  lcd.print(options[japanese_ogre_location + 1]);
  lcd.setCursor(7, (japanese_ogre_direction) ? 0 : 1);
  lcd.print("<");

  while (true) {
    char key = keypad.getKey(); // Get the pressed key
    if (key) {
      if (key == up) {
        // Handle up key
        if (japanese_ogre_direction) {
          japanese_ogre_location = (japanese_ogre_location + (optnum - 2)) % (optnum - 1);
        }
        japanese_ogre_direction = (japanese_ogre_location == optnum - 2) ? !japanese_ogre_direction : true;
      } else if (key == down) {
        // Handle down key
        if (!japanese_ogre_direction) {
          japanese_ogre_location = (japanese_ogre_location + 1) % (optnum - 1);
        }
        japanese_ogre_direction = (japanese_ogre_location == 0) ? !japanese_ogre_direction : false;
      } else if (key == select) {
        // Handle select key
        mode = options[japanese_ogre_location + !japanese_ogre_direction];
        break;
      }

      // Update the menu display
      lcd.clear();
      lcd.print(options[japanese_ogre_location]);
      lcd.setCursor(0, 1);
      lcd.print(options[japanese_ogre_location + 1]);
      lcd.setCursor(7, (japanese_ogre_direction) ? 0 : 1);
      lcd.print("<");
    }
    delay(50);
  }
}

// Function to perform calculations
void calculate() {
  // Get user input
  String user_input = get_input("f" + (String)base_1_numerator + '/' + (String)base_1_denominator + " t" + (String)base_2_numerator + '/' + (String)base_2_denominator, "calculate");
  lcd.clear();

  // Check if input is valid
  bool is_negative = (user_input[0] == '-');
  if (user_input.length() - is_negative < 0 || user_input.length() - is_negative > 16) {
    lcd.print("bad input");
    delay(1000);
    mode = "calc";
    return;
  }

  // Convert input to an array of integers
  int user_input_array[input_length] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (int i = user_input.length() - 1; i >= is_negative; i--) {
    user_input_array[input_length - user_input.length() + i] = ((int)user_input[i] <= '9') ? (int)user_input[i] - (int)'0' : (int)user_input[i] - (int)'A' + 10;
  }

  // Convert the input to a decimal number
  float decimal_number = other_to_decimal(is_negative, user_input_array, base_1_numerator, base_1_denominator);

  // Convert the decimal number to the target base
  String result = (decimal_number - round(decimal_number < 0.0001)) ? "" : "R";
  result = result + japanese_ogre_transmutation_wizard(fractional_bases(round(decimal_number), base_2_numerator, base_2_denominator));

  // Display the result
  lcd.print(user_input);
  lcd.setCursor(0, 1);
  lcd.print(result);

  // Wait for user input
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

// Function to set the base (numerator and denominator)
void set_base(int base_to_change) {
  mode = "menu";
  String user_input = get_input("Base " + String(base_to_change) + ":", "base");
  lcd.clear();

  // Validate the input
  if (user_input.indexOf('/', user_input.indexOf('/') + 1) != -1) {
    lcd.print("bad / try again");
    delay(1000);
    return;
  } else {
    bool is_negative = false;
    for (int i = user_input.indexOf('-'); i != -1; i = user_input.indexOf('-', i + 1)) {
      if (i != 0 && user_input[i - 1] != '/') {
        lcd.print("bad - try again");
        delay(1000);
        return;
      }
    }
  }

  // Parse the numerator and denominator
  int slash_index = user_input.indexOf('/');
  int numerator = user_input.substring(0, slash_index).toInt();
  int denominator = slash_index + 1 ? user_input.substring(slash_index + 1).toInt() : 1;

  // Validate the numerator and denominator
  if (!numerator || !denominator || abs(numerator) > 35 || abs(denominator) > 35 || numerator == denominator) {
    lcd.print("input error");
    delay(1000);
    return;
  }

  // Update the base
  if (base_to_change == 1) {
    base_1_numerator = numerator;
    base_1_denominator = denominator;
  } else {
    base_2_numerator = numerator;
    base_2_denominator = denominator;
  }

  // Display the updated base
  lcd.clear();
  lcd.print(numerator);
  lcd.setCursor(0, 1);
  lcd.print(denominator);
  delay(1000);
}

// Function to convert a number from another base to decimal
float other_to_decimal(bool is_negative, int other_number[input_length], int numerator, int denominator) {
  float decimal_number = 0;
  for (int i = input_length - 1; i >= 0; i--) {
    decimal_number += other_number[i] * (pow(numerator, 15 - i) / pow(denominator, 15 - i));
  }
  return is_negative ? -decimal_number : decimal_number;
}

// Function to convert a decimal number to another base
char* decimal_to_other(int decimal_number, int new_base, int denominator) {
  static char new_number_char[input_length];
  for (int i = 0; i < input_length; i++) {
    new_number_char[i] = ' ';
  }
  if (!decimal_number) {
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
  int new_number[input_length] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
  for (int i = input_length - 1; quotient != 0; i--) {
    if (i - is_negative < 0) {
      static char japanese_fucking_ogre = '|';
      return &japanese_fucking_ogre;
    }
    remainder = quotient % new_base;
    quotient = (int)quotient / new_base;
    if (remainder < 0) {
      remainder += abs(new_base);
      quotient++;
    }
    quotient *= denominator;
    new_number[i] = remainder;
  }
  for (int i = 0; i < input_length; i++) {
    if (new_number[i] != -1) {
      new_number_char[i] = int_to_char[new_number[i]];
    }
  }
  if (is_negative) {
    for (int i = 0; i < input_length - 1; i++) {
      if (new_number[i + 1] != -1) {
        new_number_char[i] = '-';
        break;
      }
    }
  }
  return new_number_char;
}

// Function to handle fractional bases
char* fractional_bases(int decimal_number, int numerator, int denominator) {
  if (numerator < 0 && denominator < 0) {
    numerator = abs(numerator);
    denominator = abs(denominator);
  }
  if (abs(denominator) > abs(numerator)) {
    if (numerator < 0 || denominator < 0) {
      denominator = -abs(denominator);
      numerator = abs(numerator);
    }
    char* flipped_result = decimal_to_other(decimal_number, denominator, numerator);
    if (*flipped_result != ' ') {
      static char japanese_fucking_ogre = '|';
      return &japanese_fucking_ogre;
    }
    static char result[input_length];
    for (int i = 0; i < input_length; i++) {
      result[i] = ' ';
    }
    int japanese_ogre_count = 0;
    for (int i = 0; i < input_length; i++) {
      if (*(flipped_result + i) == ' ') {
        result[i] = ' ';
        japanese_ogre_count++;
      } else {
        result[japanese_ogre_count + input_length - 1 - i] = *(flipped_result + i);
      }
    }
    result[japanese_ogre_count - 1] = result[japanese_ogre_count];
    result[japanese_ogre_count] = '.';
    return result;
  } else {
    if (numerator < 0 || denominator < 0) {
      denominator = abs(denominator);
      numerator = -abs(numerator);
    }
    return decimal_to_other(decimal_number, numerator, denominator);
  }
}

// Function to convert a char array to a String
String japanese_ogre_transmutation_wizard(char* ogre_wizard_test_subject) {
  if (*ogre_wizard_test_subject == '|') {
    return "subject escaped";
  }
  String transformed_japanese_ogre = "";
  for (int i = 0; i < input_length; i++) {
    if (*(ogre_wizard_test_subject + i) != ' ') {
      transformed_japanese_ogre = transformed_japanese_ogre + *(ogre_wizard_test_subject + i);
    }
  }
  return transformed_japanese_ogre;
}