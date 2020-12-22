#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "cube.h"

#include <algorithm>
#include <ranges>
#include <sstream>

std::string const example{R"(.#.
..#
###
)"};

TEST_CASE("Parse input") {
  std::istringstream input{example};
  auto const world = parse_input(input);
  auto const cells = lift(world, ThreeDimensional);

  REQUIRE(cells.size() == 5);
  REQUIRE(is_alive(cells, {1, 0, 0}));
  REQUIRE(not is_alive(cells, {1, 1, 0}));
}

TEST_CASE("count neighbors") {
  Cells world{{1, 2, 3}, {2, 2, 1}, {2, 1, 2}, {0, 2, 2}};
  REQUIRE(count_neighbors(world, {2, 2, 2}) == 3);
}

TEST_CASE("check neighbor") {
  REQUIRE(not is_neighbor({0, 0, 0}, {0, 0, 2}));
  REQUIRE(is_neighbor({0, 0, 0}, {0, 1, 0}));
}

TEST_CASE("Survive with 2 or 3 neighbors") {
  Cell const me{1, 0, 1};
  Cells world{{0, 0, 0}, {0, 0, 2}, me};
  REQUIRE(survive(world, me));

  world.push_back({2, 1, 0});
  REQUIRE(survive(world, me));
}

TEST_CASE("Die with less than 2 neighbors") {
  Cell const me{1, 0, 1};
  Cells world{{0, 0, 0}, me};
  REQUIRE(not survive(world, me));
}

TEST_CASE("Die with more than 3 neighbors") {
  Cell const me{1, 0, 1};
  Cells world{{0, 0, 0}, {1, 1, 0}, {2, 1, 2}, {1, 1, 2}, me};
  REQUIRE(not survive(world, me));
}

TEST_CASE("Surrounding cells of single cell") {
  Cells world{{2, 2, 2}};

  auto const surrounding = find_surrounding(world);
  REQUIRE(surrounding.size() == 26);

  REQUIRE(std::ranges::find(surrounding, Cell{1, 1, 2}) != surrounding.end());
  REQUIRE(std::ranges::find(surrounding, Cell{3, 2, 1}) != surrounding.end());

  REQUIRE(std::ranges::find(surrounding, Cell{2, 2, 2}) == surrounding.end());
  REQUIRE(std::ranges::find(surrounding, Cell{0, 2, 2}) == surrounding.end());
}

TEST_CASE("Overlapping urrounding cells") {
  Cells world{{10, 10, 10}, {11, 11, 11}};

  auto const surrounding = find_surrounding(world);
  REQUIRE(surrounding.size() == 44);

  REQUIRE(std::ranges::find(surrounding, Cell{10, 11, 10}) !=
          surrounding.end());
  REQUIRE(std::ranges::find(surrounding, Cell{9, 10, 10}) != surrounding.end());
  REQUIRE(std::ranges::find(surrounding, Cell{10, 11, 12}) !=
          surrounding.end());

  REQUIRE(std::ranges::find(surrounding, Cell{10, 10, 10}) ==
          surrounding.end());
  REQUIRE(std::ranges::find(surrounding, Cell{11, 11, 11}) ==
          surrounding.end());
}

TEST_CASE("new cell is born if 3 neighbors") {
  Cells world{{4, 5, 4}, {4, 5, 3}, {3, 5, 4}};

  REQUIRE(new_born(world, {4, 4, 4}));

  REQUIRE(not new_born(world, {5, 5, 4}));
  REQUIRE(not new_born(world, {4, 5, 5}));

  world.push_back({3, 4, 3});
  REQUIRE(not new_born(world, {4, 4, 4}));
}

TEST_CASE("Example - Part I") {
  std::istringstream input{example};
  auto world = parse_input(input);
  world = lift(world, ThreeDimensional);

  for (uint i = 0; i < 6; ++i) {
    world = tick(world);
  }

  REQUIRE(world.size() == 112);
}
