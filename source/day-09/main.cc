#include "xmas.h"

#include <iostream>

int main() {
  auto const values = parse_input(std::cin);
  auto const weak = find_weakness(25, values);
  auto const weakness = break_weakness(weak, values);

  std::cout << weak << "\n";
  std::cout << weakness << "\n";
}