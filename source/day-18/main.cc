#include "math.h"

#include <iostream>

int main() {
  auto const result = total_sum(std::cin);
  std::cout << "New math :          " << result.first << "\n";
  std::cout << "Advanced new math : " << result.second << "\n";
}
