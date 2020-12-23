#include "cups.h"

#include <iostream>

int main() {
  auto cups = parse_input("962713854");
  make_moves(cups, 100);
  auto const result = print_after(cups, 1);

  std::cout << "Part I : " << result << "\n";

  auto a_million = parse_input("962713854", 1000000);
  make_moves(a_million, 10000000);
  auto const [one, two] = pair_after(a_million, 1);

  std::cout << "Part II : " << calc_result(one, two) << "\n";
}
