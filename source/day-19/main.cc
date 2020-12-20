#include "message.h"

#include <iostream>

int main() {
  auto const [language, messages] = parse_input(std::cin);
  auto const normalized = normalize(language);

  auto const valid = count_valid(normalized, messages);
  std::cout << valid << "\n";

  auto const fixed = fix_rules(language);
  auto const fixed_cnf = normalize(fixed);

  auto const valid_fixed = count_valid(fixed_cnf, messages);
  std::cout << valid_fixed << "\n";
}