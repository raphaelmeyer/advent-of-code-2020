#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "xmas.h"

#include <sstream>

TEST_CASE("example") {
  std::string const data{R"(35
20
15
25
47
40
62
55
65
95
102
117
150
182
127
219
299
277
309
576
)"};

  std::istringstream input{data};

  auto const values = parse_input(input);
  auto const weak = find_weakness(5, values);
  REQUIRE(weak == 127);
  REQUIRE(break_weakness(weak, values) == 62);
}

// 26796446
