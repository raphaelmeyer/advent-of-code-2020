#include "port.h"

#include <iostream>

int main() {
  auto const program = parse_input(std::cin);

  auto const memory = run_program(program);
  std::cout << "Part I : " << sum_mem(memory) << "\n";

  auto const memory2 = run_program_v2(program);
  std::cout << "Part II : " << sum_mem(memory2) << "\n";
}
