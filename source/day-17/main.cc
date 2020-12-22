#include "cube.h"

#include <iostream>

int main() {
  auto world = parse_input(std::cin);

  auto three_dim = lift(world, ThreeDimensional);
  for (uint i = 0; i < 6; ++i) {
    three_dim = tick(three_dim);
  }
  std::cout << "Part I : " << three_dim.size() << "\n";

  auto four_dim = lift(world, FourDimensional);
  for (uint i = 0; i < 6; ++i) {
    four_dim = tick(four_dim);
  }
  std::cout << "Part II : " << four_dim.size() << "\n";
}
