#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "cups.h"

TEST_CASE("Example - Part I") {
  auto cups = parse_input("389125467");

  make_moves(cups, 100);
  auto const result = print_after(cups, 1);

  REQUIRE(result == "67384529");
}

TEST_CASE("Parse input") {
  auto const cups = parse_input("851673942");

  REQUIRE(cups.size() == 10);
  REQUIRE(cups == Cups{8, 6, 8, 9, 2, 1, 7, 3, 5, 4});
}

TEST_CASE("A normal move") {
  auto cups = parse_input("389125467");

  move(cups);

  auto const expected = parse_input("289154673");
  REQUIRE(cups == expected);
}

TEST_CASE("A move with new current in picked up cups") {
  auto cups = parse_input("546789132");

  move(cups);

  auto const expected = parse_input("891346725");
  REQUIRE(cups == expected);
}

TEST_CASE("A move with sequence of new currents in picked up cups") {
  auto cups = parse_input("289154673");

  move(cups);

  auto const expected = parse_input("546789132");
  REQUIRE(cups == expected);
}

TEST_CASE("Make 10 moves") {
  auto cups = parse_input("389125467");

  make_moves(cups, 10);

  auto const expected = parse_input("837419265");
  REQUIRE(cups == expected);
}

TEST_CASE("Print after cup #label") {
  REQUIRE(print_after(parse_input("123456789"), 1) == "23456789");
  REQUIRE(print_after(parse_input("389125467"), 7) == "38912546");
  REQUIRE(print_after(parse_input("389125467"), 4) == "67389125");
}

TEST_CASE("Use more cups") {
  auto cups = parse_input("389125467", 100);

  REQUIRE(cups.size() == 101);

  REQUIRE(cups[0] == 3);
  REQUIRE(cups[3] == 8);
  REQUIRE(cups[7] == 10);
  REQUIRE(cups[10] == 11);
  REQUIRE(cups[11] == 12);
  REQUIRE(cups[99] == 100);
  REQUIRE(cups[100] == 3);
}

TEST_CASE("Example - Part II") {
  auto cups = parse_input("389125467", 1000000);

  make_moves(cups, 10000000);

  auto const [one, two] = pair_after(cups, 1);

  REQUIRE(one == 934001);
  REQUIRE(two == 159792);

  REQUIRE(calc_result(one, two) == 149245887792);
}
