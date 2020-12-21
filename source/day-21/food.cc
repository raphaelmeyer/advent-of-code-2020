#include "food.h"

#include <algorithm>
#include <numeric>
#include <ranges>
#include <regex>

Foods parse_input(std::istream &input) {
  Foods foods{};

  std::string line{};
  std::regex pattern{R"(\w+)"};
  while (std::getline(input, line)) {
    Food food{};

    std::sregex_token_iterator it{line.begin(), line.end(), pattern};
    std::sregex_token_iterator end;

    while (it != end && *it != "contains") {
      food.ingredients.push_back(*it);
      ++it;
    }
    ++it;

    while (it != end) {
      food.allergens.push_back(*it);
      ++it;
    }

    std::ranges::sort(food.ingredients);
    foods.push_back(food);
  }

  return foods;
}

uint count_safe_ingredients(Foods const &foods, List const &safe) {
  return std::accumulate(
      foods.begin(), foods.end(), 0, [&safe](uint acc, Food const &food) {
        return acc + std::ranges::count_if(
                         food.ingredients, [&safe](auto const &ingredient) {
                           return std::ranges::find(safe, ingredient) !=
                                  safe.end();
                         });
      });
}

List all_ingredients(Foods const &foods) {
  List ingredients{};

  for (auto const food : foods) {
    std::ranges::copy(food.ingredients, std::back_inserter(ingredients));
  }

  std::ranges::sort(ingredients);
  auto [last, end] = std::ranges::unique(ingredients);
  ingredients.erase(last, end);

  return ingredients;
}

List all_allergens(Foods const &foods) {
  List allergens{};

  for (auto const food : foods) {
    std::ranges::copy(food.allergens, std::back_inserter(allergens));
  }

  std::ranges::sort(allergens);
  auto [last, end] = std::ranges::unique(allergens);
  allergens.erase(last, end);

  return allergens;
}

Allergic find_allergic_ingredients(Foods const &foods) {
  std::map<std::string, List> may_contain{};

  auto const allergens = all_allergens(foods);
  for (auto allergen : allergens) {
    auto food_with_allergen =
        std::ranges::views::filter(foods, [&allergen](auto const &food) {
          return std::ranges::find(food.allergens, allergen) !=
                 food.allergens.end();
        });

    List acc{food_with_allergen.front().ingredients};
    List intersection{};
    for (auto const &food : food_with_allergen) {
      std::ranges::set_intersection(acc, food.ingredients,
                                    std::back_inserter(intersection));
      std::ranges::swap(acc, intersection);
      intersection.clear();
    }

    for (auto const &ingredient : acc) {
      may_contain[ingredient].push_back(allergen);
    }
  }

  Allergic allergic_ingredients{};

  while (not may_contain.empty()) {
    auto match = std::ranges::find_if(
        may_contain, [](auto const &may) { return may.second.size() == 1; });

    if (match == may_contain.end()) {
      throw std::out_of_range{"no"};
    }

    auto const allergen = match->second.front();
    allergic_ingredients[match->first] = allergen;

    for (auto &may : may_contain) {
      std::erase(may.second, allergen);
    }
    may_contain.erase(match);
  }

  return allergic_ingredients;
}

List find_safe_ingredients(Foods const &foods, Allergic const &allergic) {
  auto const ingredients = all_ingredients(foods);

  List safe{};
  std::ranges::copy_if(ingredients, std::back_inserter(safe),
                       [&allergic](auto const &ingredient) {
                         return not allergic.contains(ingredient);
                       });

  return safe;
}

std::string canonical_dangerous_ingredient_list(Allergic const &allergic) {
  Allergic swapped{};
  std::ranges::transform(
      allergic, std::inserter(swapped, swapped.end()), [](auto e) {
        return std::pair<std::string, std::string>{e.second, e.first};
      });
  auto const sorted = swapped | std::ranges::views::values;

  std::ostringstream list{};
  std::string delim{};
  for (auto const &ingredient : sorted) {
    list << delim << ingredient;
    delim = ",";
  }

  return list.str();
}
