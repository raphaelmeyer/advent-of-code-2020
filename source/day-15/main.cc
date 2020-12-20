#include "game.h"

#include <iostream>

int main() {
  std::cout << nth_number("12,1,16,3,11,0", 2020) << "\n";
  std::cout << nth_number("12,1,16,3,11,0", 30000000) << "\n";
}
