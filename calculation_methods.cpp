#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>
using namespace std;

char int_to_char[36] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
unordered_map<char, int> chat_to_int =
{
  {'0', 0},
  {'1', 1},
  {'2', 2},
  {'3', 3},
  {'4', 4},
  {'5', 5},
  {'6', 6},
  {'7', 7},
  {'8', 8},
  {'9', 9},
  {'A', 10},
  {'B', 11},
  {'C', 12},
  {'D', 13},
  {'E', 14},
  {'F', 15},
  {'G', 16},
  {'H', 17},
  {'I', 18},
  {'J', 19},
  {'K', 20},
  {'L', 21},
  {'M', 22},
  {'N', 23},
  {'O', 24},
  {'P', 25},
  {'Q', 26},
  {'R', 27},
  {'S', 28},
  {'T', 29},
  {'U', 30},
  {'V', 31},
  {'W', 32},
  {'X', 33},
  {'Y', 34},
  {'Z', 35},
};

void print_vector(vector<char> input){
    int vector_size = static_cast<char>(input.size());
    for(int i = 0; i < vector_size; i++) {
        cout<< input[i] <<"";
    }
    cout<< "\n";
}

int other_to_decimal(int other_number[8], int base) {
  int decimal_number = 0;
  for (int i = 7; i >= 0; i--) {
    if (other_number[i]){
      decimal_number += pow(base, 7-i);
    }
  }
  return decimal_number;
}

vector<char> decimal_to_other(int decimal_number, int new_base) {
    vector<char> new_number_char = {};
      bool is_negativ;
      if (decimal_number < 0) {
        is_negativ = true;
        decimal_number = abs(decimal_number);
      }
      else {
        is_negativ = false;
      }
      int remainder = 0;
      int quotient = decimal_number;
      vector<int> new_number = {};

      for (; quotient != 0;){
          remainder = quotient % new_base;
          quotient = (int) quotient / new_base;
          if (remainder < 0) {
            remainder += abs(new_base);
            quotient ++;
          }
          new_number.insert(new_number.begin(), remainder); // inserts remainder at the begin of the number
      }
      int vector_size = static_cast<int>(new_number.size());
      for (int i = 0; i < vector_size; i++){
        new_number_char.push_back(int_to_char[new_number[i]]);
      }
      if (is_negativ) {
        new_number_char.insert(new_number_char.begin(), '-');
      }
      return new_number_char;
}

int main() {
    int input_number[8] = {1, 0, 1, 0, 0, 0, 1, 0};
    int decimal_number = other_to_decimal(input_number, 2);
    cout<< "Other to decimal:" <<endl;
    cout<< decimal_number <<endl;
    int new_base = -2;
    vector<char> test = decimal_to_other(2, new_base);
    cout<< "Decimal to" << " ";
    cout<< new_base << ":\n";
    print_vector(test);
    return 0;
}


