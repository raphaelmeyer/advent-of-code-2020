#include "slope.h"

#include <iostream>

int main() {
  Grid grid{};
  grid.parse(std::cin);

  std::cout << "Part I : " << count_trees(grid, {{3, 1}}) << "\n";

  std::vector<Slope> slopes{{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};
  std::cout << "Part II : " << count_trees(grid, slopes) << "\n";
}