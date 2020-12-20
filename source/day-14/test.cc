#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "port.h"

#include <sstream>

std::string example{R"(mask = XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X
mem[8] = 11
mem[7] = 101
mem[8] = 0
)"};

TEST_CASE("Example - Part I") {
  std::istringstream input{example};

  auto const program = parse_input(input);
  auto const memory = run_program(program);

  REQUIRE(sum_mem(memory) == 165);
}

TEST_CASE("Example - Part II") {
  std::string const data{R"(mask = 000000000000000000000000000000X1001X
mem[42] = 100
mask = 00000000000000000000000000000000X0XX
mem[26] = 1
)"};
  std::istringstream input{data};

  auto const program = parse_input(input);
  auto const memory = run_program_v2(program);

  REQUIRE(sum_mem(memory) == 208);
}

TEST_CASE("Parse Input") {
  std::istringstream input{example};

  auto const program = parse_input(input);

  REQUIRE(program.size() == 4);

  REQUIRE(std::holds_alternative<UpdateMask>(program[0]));
  REQUIRE(std::holds_alternative<UpdateMemory>(program[2]));

  auto const mask = std::get<UpdateMask>(program[0]);
  REQUIRE(mask.mask == 0b111111111111111111111111111110111101);
  REQUIRE(mask.value == 0b000000000000000000000000000001000000);

  auto const mem = std::get<UpdateMemory>(program[2]);
  REQUIRE(mem.address == 7);
  REQUIRE(mem.value == 101);
}

TEST_CASE("Run Program") {
  std::istringstream input{example};
  auto const program = parse_input(input);

  auto const memory = run_program(program);

  REQUIRE(memory.size() == 2);
  REQUIRE(memory.contains(7));
  REQUIRE(memory.contains(8));
}
