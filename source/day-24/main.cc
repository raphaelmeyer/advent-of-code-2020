#include "tiles.h"

#include <iostream>

int main() {
  auto instruction = parse_input(std::cin);
  auto tiles = flip_tiles(instruction);
  auto const black = count(tiles, Side::Black);
  std::cout << "Part I : " << black << "\n";

  tiles = update(tiles, 100);
  std::cout << "Part II : " << count(tiles, Side::Black) << "\n";
}
