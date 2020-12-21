#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "password.h"

TEST_CASE("Password Philosophy") {
  auto const data = R"data(1-3 a: abcde
1-3 b: cdefg
2-9 c: ccccccccc
)data";

  std::istringstream input{data};
  auto const passwords = parse_input(input);

  REQUIRE(count_valid_passwords<OldPolicy>(passwords) == 2);
}

TEST_CASE("Verify password according to policy") {
  OldPolicy policy{};

  REQUIRE(policy("1-3 a: abcde"));
  REQUIRE(not policy("1-3 b: cdefg"));
}

TEST_CASE("Password Philosophy - with new policy") {
  auto const data = R"data(1-3 a: abcde
1-3 b: cdefg
2-9 c: ccccccccc
)data";

  std::istringstream input{data};
  auto const passwords = parse_input(input);

  REQUIRE(count_valid_passwords<NewPolicy>(passwords) == 1);
}

TEST_CASE("Verify password according to policy") {
  NewPolicy policy{};

  REQUIRE(policy("1-3 a: abcde"));
  REQUIRE(not policy("1-3 b: cdefg"));
  REQUIRE(not policy("2-9 c: ccccccccc"));
}
