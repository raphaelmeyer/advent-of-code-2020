#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "door.h"

TEST_CASE("Example - Part I") { REQUIRE(true); }

TEST_CASE("Example - Part II") { REQUIRE(true); }

TEST_CASE("transform") {
  REQUIRE(transform(7, 8) == 5764801);
  REQUIRE(transform(7, 11) == 17807724);
}

TEST_CASE("shared secret") {
  REQUIRE(transform(5764801, 11) == 14897079);
  REQUIRE(transform(17807724, 8) == 14897079);
}

TEST_CASE("brute force") {
  REQUIRE(brute_force(7, 5764801) == 8);
  REQUIRE(brute_force(7, 17807724) == 11);
}
