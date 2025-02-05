#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


void print_vector(vector<int> input){
    int vector_size = static_cast<int>(input.size());
    for(int i = 0; i < vector_size; i++) {
        cout<< input[i] <<"";
    }
    cout<< "\n";
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

vector<int> decimal_to_other(int decimal_number, int new_base) {
    int remainder = 0;
    int quotient = decimal_number;
    vector<int> new_number = {};

    for (; quotient > 0;){
        remainder = quotient % new_base;
        quotient = (int) quotient / new_base;
        new_number.insert(new_number.begin(), remainder); // inserts remainder at the begin of the number
    }
/*
    if (new_base > 10) {
      int vector_size = static_cast<int>(new_number.size());
      for (int i = 0; i < vector_size; i++){
      }
    }
*/
    return new_number;
}


int main() {
    int input_number[8] = {1, 0, 1, 0, 0, 0, 1, 0};
    int decimal_number = binary_to_decimal(input_number);
    cout<< "Binary to decimal:" <<endl;
    cout<< decimal_number <<endl;
    int new_base = 11;
    vector<int> test = decimal_to_other(234, new_base);
    cout<< "Decimal to" << " ";
    cout<< new_base << ":\n";
    print_vector(test);
    return 0;
}


