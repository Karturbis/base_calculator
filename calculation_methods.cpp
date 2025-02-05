#include <iostream>
#include <cmath>

int to_decimal(int binary_number[8]) {
  int decimal_number = 0;
  for (int i = 7; i >= 0; i--) {
    if (binary_number[i]){
      decimal_number += pow(2, 7-i);
    }
  }
  return decimal_number;
}


int main() {
    int input_number[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int s = to_decimal(input_number);
    std::cout<< s <<std::endl;
    return 0;
}


