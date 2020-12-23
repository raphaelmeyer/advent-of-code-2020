#include "ferry.h"

#include <iostream>

int main() {
  auto const instructions = parse_input(std::cin);

  auto position = move_ferry(instructions, Direction::East);
  std::cout << "Part I : " << std::abs(position.x) + std::abs(position.y)
            << "\n";

  position = move_waypoint(instructions, {10, 1});
  std::cout << "Part II : " << std::abs(position.x) + std::abs(position.y)
            << "\n";
}