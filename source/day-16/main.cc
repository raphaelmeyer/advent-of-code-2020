#include "ticket.h"

#include <iostream>

int main() {
  auto const data = parse_input(std::cin);
  std::cout << "Part I : " << error_rate(data) << "\n";

  auto const result = calculate_solution(data);
  std::cout << "Part II : " << result << "\n";
}
