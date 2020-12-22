#include "cards.h"

#include <iostream>

int main() {
  auto const start = parse_input(std::cin);

  auto const game1 = play(start);
  std::cout << "Part I : " << calculate_score(game1) << "\n";

  auto const game2 = play_recursive(start);
  std::cout << "Part II : " << calculate_score(game2) << "\n";
}
