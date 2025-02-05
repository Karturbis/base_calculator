#include <iostream>
#include <cmath>

int base_10(int base_2_number[8]) {
  int base_10_number = 0;
  for (int i = 7; i >= 0; i--) {
    if (base_2_number[i]){
      base_10_number += pow(2, 7-i);
    }
  }
  return base_10_number;
}


int main() {
    int input_number[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int s = base_10(input_number);
    std::cout<< s <<std::endl;
    return 0;
}


