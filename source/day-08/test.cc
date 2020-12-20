#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "boot.h"

#include <sstream>

std::string const data{R"(nop +0
acc +1
jmp +4
acc +3
jmp -3
acc -99
acc +1
jmp -4
acc +6
)"};

TEST_CASE("find loop") {
  std::istringstream input{data};
  auto const program = parse_code(input);

  auto const result = find_loop(program);
  REQUIRE(result.loop);
  REQUIRE(result.acc == 5);
}

TEST_CASE("parse code") {
  std::istringstream input{data};
  auto const program = parse_code(input);
  REQUIRE(program.size() == 9);
  REQUIRE(program[5].ins == "acc");
  REQUIRE(program[5].off == -99);
}
