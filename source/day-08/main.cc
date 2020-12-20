#include "boot.h"

#include <iostream>

int main() {
  auto const program = parse_code(std::cin);
  auto const result = find_loop(program);

  if (result.loop) {
    std::cout << "acc = " << result.acc << "\n";
  }

  auto const end = fix_code(program);
  std::cout << "fixed acc = " << end << "\n";
}