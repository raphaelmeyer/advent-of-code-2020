#pragma once

#include <istream>
#include <vector>

struct Diffs {
  uint one;
  uint two;
  uint three;
};

std::vector<uint> parse_input(std::istream &input);
Diffs connect_jolt_adapters(std::vector<uint> const &adapters);
uint64_t jolt_permutations(std::vector<uint> const &adapters);

uint64_t count_permutations(uint length);
