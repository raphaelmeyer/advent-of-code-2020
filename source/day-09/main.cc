#include "xmas.h"

#include <iostream>

int main() {
  auto const values = parse_input(std::cin);
  auto const weak = find_weakness(25, values);
  auto const weakness = break_weakness(weak, values);

  std::cout << "Part I : " << weak << "\n";
  std::cout << "Part II : " << weakness << "\n";
}
