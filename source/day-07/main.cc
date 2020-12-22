#include "bag.h"

#include <iostream>

int main() {
  auto const rules = parse_rules(std::cin);

  std::cout << "Part I : " << count_bags_containing(rules, "shiny gold")
            << "\n";

  std::cout << "Part II : " << count_contained_bags(rules, "shiny gold")
            << "\n";
}
