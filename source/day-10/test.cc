#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "jolt.h"

#include <sstream>

std::string const data{R"(28
33
18
42
31
14
46
20
48
47
24
23
49
45
19
38
39
11
1
32
25
35
8
17
7
9
4
2
34
10
3
)"};

TEST_CASE("example") {
  std::istringstream input{data};

  auto const adapters = parse_input(input);
  auto const diffs = connect_jolt_adapters(adapters);

  REQUIRE(diffs.one == 22);
  REQUIRE(diffs.three == 10);
}

TEST_CASE("example part II") {
  std::istringstream input{data};

  auto const adapters = parse_input(input);
  auto const permutations = jolt_permutations(adapters);

  REQUIRE(permutations == 19208);
}

TEST_CASE("count permutations") {
  REQUIRE(count_permutations(1) == 1);
  REQUIRE(count_permutations(2) == 2);
  REQUIRE(count_permutations(3) == 4);
  REQUIRE(count_permutations(4) == 7);
}
