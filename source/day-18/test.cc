#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "math.h"
#include "parser.h"

TEST_CASE("Examples - Part I") {
  std::string input{};
  uint64_t expected{};

  SUBCASE("Example 1") {
    input = "1 + 2 * 3 + 4 * 5 + 6";
    expected = 71;
  }
  SUBCASE("Example 2") {
    input = "1 + (2 * 3) + (4 * (5 + 6))";
    expected = 51;
  }
  SUBCASE("Example 3") {
    input = "2 * 3 + (4 * 5)";
    expected = 26;
  }
  SUBCASE("Example 4") {
    input = "5 + (8 * 3 + 9 + 3 * 4 * 3)";
    expected = 437;
  }
  SUBCASE("Example 5") {
    input = "5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))";
    expected = 12240;
  }
  SUBCASE("Example 6") {
    input = "((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2";
    expected = 13632;
  }

  REQUIRE(evaluate(input) == expected);
}

TEST_CASE("Examples - Part II") {
  std::string input{};
  uint64_t expected{};

  SUBCASE("Example 2") {
    input = "1 + (2 * 3) + (4 * (5 + 6))";
    expected = 51;
  }
  SUBCASE("Example 3") {
    input = "2 * 3 + (4 * 5)";
    expected = 46;
  }
  SUBCASE("Example 4") {
    input = "5 + (8 * 3 + 9 + 3 * 4 * 3)";
    expected = 1445;
  }
  SUBCASE("Example 5") {
    input = "5 * 9 * (7 * 3 * 3 + 9 * 3 + (8 + 6 * 4))";
    expected = 669060;
  }
  SUBCASE("Example 6") {
    input = "((2 + 4 * 9) * (6 + 9 * 8 + 6) + 6) + 2 + 4 * 2";
    expected = 23340;
  }

  REQUIRE(evaluate_advanced(input) == expected);
}
