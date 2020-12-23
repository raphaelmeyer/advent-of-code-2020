#include "message.h"

#include <iostream>

int main() {
  auto const [language, messages] = parse_input(std::cin);
  auto const normalized = normalize(language);

  auto const valid = count_valid(normalized, messages);
  std::cout << "Part I : " << valid << "\n";

  auto const fixed = fix_rules(language);
  auto const fixed_cnf = normalize(fixed);

  auto const valid_fixed = count_valid(fixed_cnf, messages);
  std::cout << "Part II : " << valid_fixed << "\n";
}