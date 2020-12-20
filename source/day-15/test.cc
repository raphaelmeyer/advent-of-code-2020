#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "game.h"

TEST_CASE("Part I") {
  REQUIRE(nth_number("1,3,2", 2020) == 1);
  REQUIRE(nth_number("2,1,3", 2020) == 10);
  REQUIRE(nth_number("1,2,3", 2020) == 27);
  REQUIRE(nth_number("2,3,1", 2020) == 78);
  REQUIRE(nth_number("3,2,1", 2020) == 438);
  REQUIRE(nth_number("3,1,2", 2020) == 1836);
}

TEST_CASE("Part II") {
  // REQUIRE(nth_number("0,3,6", 30000000) == 175594);
  // REQUIRE(nth_number("1,3,2", 30000000) == 2578);
  // REQUIRE(nth_number("2,1,3", 30000000) == 3544142);
  // REQUIRE(nth_number("1,2,3", 30000000) == 261214);
  // REQUIRE(nth_number("2,3,1", 30000000) == 6895259);
  // REQUIRE(nth_number("3,2,1", 30000000) == 18);
  // REQUIRE(nth_number("3,1,2", 30000000) == 362);
}
