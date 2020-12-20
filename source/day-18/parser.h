#pragma once

#include <string>

enum class Math { New, Advanced };

uint64_t parse_expression(std::string input, Math math);
