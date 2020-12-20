#include "jigsaw.h"

#include <iostream>

int main() {
  auto const [tiles, images] = parse_input(std::cin);
  auto const arrangement = solve_puzzle(tiles);
  auto const solution = corner_product(arrangement);

  std::cout << "Part I : " << solution << "\n";

  auto const full_image = create_image(images, arrangement);
  auto const marked = mark_monsters(full_image);
  auto const roughness = count_roughness(marked);
  std::cout << "Part II : " << roughness << "\n";
}
