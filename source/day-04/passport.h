#pragma once

#include <istream>
#include <string>
#include <vector>

enum class Version { One, Two };

std::vector<std::string> parse_input(std::istream &input);
uint count_valid_passports(std::vector<std::string> const &passport_data,
                           Version version);
