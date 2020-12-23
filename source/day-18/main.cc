#include "math.h"

#include <iostream>

int main() {
  auto const result = total_sum(std::cin);
  std::cout << "Part I : " << result.first << "\n";
  std::cout << "Part II : " << result.second << "\n";
}
