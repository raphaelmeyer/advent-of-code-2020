#pragma once

#include <istream>
#include <map>
#include <string>
#include <vector>

using List = std::vector<std::string>;
using Allergic = std::map<std::string, std::string>;

struct Food {
  List ingredients;
  List allergens;
};
using Foods = std::vector<Food>;

Foods parse_input(std::istream &input);
uint count_safe_ingredients(Foods const &foods, List const &safe);
std::string canonical_dangerous_ingredient_list(Allergic const &allergic);

List all_allergens(Foods const &foods);
List all_ingredients(Foods const &foods);

Allergic find_allergic_ingredients(Foods const &foods);
List find_safe_ingredients(Foods const &foods, Allergic const &allergic);
