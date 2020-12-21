#include "food.h"

#include <iostream>

int main() {
  auto const foods = parse_input(std::cin);
  auto const allergic = find_allergic_ingredients(foods);
  auto const safe = find_safe_ingredients(foods, allergic);
  auto const count_safe = count_safe_ingredients(foods, safe);
  std::cout << "Part I : " << count_safe << "\n";

  auto const list = canonical_dangerous_ingredient_list(allergic);
  std::cout << "Part II : " << list << "\n";
}
