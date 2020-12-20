#include "math.h"

#include "parser.h"

std::pair<uint64_t, uint64_t> total_sum(std::istream &input) {
  uint64_t sum = 0;
  uint64_t other = 0;

  std::string line{};
  while (std::getline(input, line)) {
    sum += evaluate(line);
    other += evaluate_advanced(line);
  }

  return {sum, other};
}

uint64_t evaluate(std::string input) {
  return parse_expression(input, Math::New);
}
uint64_t evaluate_advanced(std::string input) {
  return parse_expression(input, Math::Advanced);
}
