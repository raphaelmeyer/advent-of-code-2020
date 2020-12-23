#include "boot.h"

#include <iostream>

int main() {
  auto const program = parse_code(std::cin);

  auto const result = find_loop(program);
  std::cout << "Part I : " << result.acc << "\n";

  auto const end = fix_code(program);
  std::cout << "Part II : " << end << "\n";
}