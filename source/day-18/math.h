#pragma once

#include <istream>
#include <string>
#include <utility>

std::pair<uint64_t, uint64_t> total_sum(std::istream &input);

uint64_t evaluate(std::string input);
uint64_t evaluate_advanced(std::string input);
