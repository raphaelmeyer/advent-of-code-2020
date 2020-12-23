#pragma once

#include <string>
#include <utility>
#include <vector>

using Cups = std::vector<uint>;

Cups parse_input(std::string input, uint total = 0);

void make_moves(Cups &cups, uint times);
void move(Cups &cups);

std::string print_after(Cups cups, uint label);
std::pair<uint, uint> pair_after(Cups cups, uint label);
int64_t calc_result(uint one, uint two);
