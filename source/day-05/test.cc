#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "seat.h"

TEST_CASE("Row") {
  std::string input{};
  uint expected = 0;

  SUBCASE("BFFFBBFRRR") {
    input = "BFFFBBFRRR";
    expected = 70;
  }
  SUBCASE("FFFBBBFRRR") {
    input = "FFFBBBFRRR";
    expected = 14;
  }
  SUBCASE("BBFFBBFRLL") {
    input = "BBFFBBFRLL";
    expected = 102;
  }

  REQUIRE(seat_row(input) == expected);
}

TEST_CASE("Column") {
  std::string input{};
  uint expected = 0;

  SUBCASE("BFFFBBFRRR") {
    input = "BFFFBBFRRR";
    expected = 7;
  }
  SUBCASE("FFFBBBFRRR") {
    input = "FFFBBBFRRR";
    expected = 7;
  }
  SUBCASE("BBFFBBFRLL") {
    input = "BBFFBBFRLL";
    expected = 4;
  }

  REQUIRE(seat_column(input) == expected);
}

TEST_CASE("Seat ID") {
  std::string input{};
  uint expected = 0;

  SUBCASE("BFFFBBFRRR") {
    input = "BFFFBBFRRR";
    expected = 567;
  }
  SUBCASE("FFFBBBFRRR") {
    input = "FFFBBBFRRR";
    expected = 119;
  }
  SUBCASE("BBFFBBFRLL") {
    input = "BBFFBBFRLL";
    expected = 820;
  }

  REQUIRE(decode_seat(input).id == expected);
}
