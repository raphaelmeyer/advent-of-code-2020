#pragma once

#include <istream>
#include <vector>

std::vector<uint64_t> parse_input(std::istream &input);

uint64_t find_weakness(uint preamble, std::vector<uint64_t> const &values);
uint64_t break_weakness(uint64_t weak, std::vector<uint64_t> const &values);
