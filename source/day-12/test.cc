#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "ferry.h"

#include <sstream>

std::string example{R"(F10
N3
F7
R90
F11
)"};

TEST_CASE("Example - Part I") {
  std::istringstream input{example};

  auto const instructions = parse_input(input);
  auto const position = move_ferry(instructions, Direction::East);

  REQUIRE(std::abs(position.x) + std::abs(position.y) == 25);
}

TEST_CASE("Example - Part I") {
  std::istringstream input{example};

  auto const instructions = parse_input(input);
  auto const position = move_waypoint(instructions, {10, 1});

  REQUIRE(std::abs(position.x) + std::abs(position.y) == 286);
}
