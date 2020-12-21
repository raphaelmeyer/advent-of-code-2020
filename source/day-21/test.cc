#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "food.h"

#include <sstream>

std::string const example{R"(mxmxvkd kfcds sqjhc nhms (contains dairy, fish)
trh fvjkl sbzzf mxmxvkd (contains dairy)
sqjhc fvjkl (contains soy)
sqjhc mxmxvkd sbzzf (contains fish)
)"};

TEST_CASE("Example - Part I") {
  std::istringstream input{example};
  auto const foods = parse_input(input);

  auto const allergic = find_allergic_ingredients(foods);
  auto const safe = find_safe_ingredients(foods, allergic);

  auto const count_safe = count_safe_ingredients(foods, safe);

  REQUIRE(count_safe == 5);
}

TEST_CASE("Example - Part II") {
  std::istringstream input{example};
  auto const foods = parse_input(input);
  auto const allergic = find_allergic_ingredients(foods);

  auto const list = canonical_dangerous_ingredient_list(allergic);

  REQUIRE(list == "mxmxvkd,sqjhc,fvjkl");
}

TEST_CASE("Parse Input") {
  std::istringstream input{example};
  auto const foods = parse_input(input);

  REQUIRE(foods.size() == 4);

  REQUIRE(foods[0].ingredients.size() == 4);
  REQUIRE(foods[0].ingredients[0] == "kfcds");
  REQUIRE(foods[0].ingredients[1] == "mxmxvkd");
  REQUIRE(foods[0].ingredients[2] == "nhms");
  REQUIRE(foods[0].ingredients[3] == "sqjhc");

  REQUIRE(foods[0].allergens.size() == 2);
  REQUIRE(foods[0].allergens[1] == "fish");

  REQUIRE(foods[2].ingredients.size() == 2);
  REQUIRE(foods[2].ingredients[0] == "fvjkl");
  REQUIRE(foods[2].ingredients[1] == "sqjhc");

  REQUIRE(foods[2].allergens.size() == 1);
  REQUIRE(foods[2].allergens[0] == "soy");
}

TEST_CASE("List all ingredients") {
  Foods foods{{{"tuna", "garlic", "milk"}, {"dairy", "fish"}},
              {{"milk", "cilantro"}, {"dairy"}},
              {{"cilantro", "tofu", "garlic"}, {"soy"}}};

  auto const ingredients = all_ingredients(foods);

  REQUIRE(ingredients.size() == 5);

  REQUIRE(std::ranges::find(ingredients, "garlic") != ingredients.end());
  REQUIRE(std::ranges::find(ingredients, "tofu") != ingredients.end());

  REQUIRE(std::ranges::find(ingredients, "fish") == ingredients.end());
}

TEST_CASE("List all allergens") {
  Foods foods{{{"tuna", "garlic", "milk"}, {"dairy", "fish"}},
              {{"milk", "cilantro"}, {"dairy"}},
              {{"cilantro", "tofu", "garlic"}, {"soy"}}};

  auto const allergens = all_allergens(foods);

  REQUIRE(allergens.size() == 3);

  REQUIRE(std::ranges::find(allergens, "dairy") != allergens.end());
  REQUIRE(std::ranges::find(allergens, "fish") != allergens.end());
  REQUIRE(std::ranges::find(allergens, "soy") != allergens.end());

  REQUIRE(std::ranges::find(allergens, "cilantro") == allergens.end());
}

TEST_CASE("Allergic ingredients") {
  std::istringstream input{example};
  auto const foods = parse_input(input);

  auto const allergic = find_allergic_ingredients(foods);

  REQUIRE(allergic.size() == 3);

  REQUIRE(allergic.at("sqjhc") == "fish");
  REQUIRE(allergic.at("mxmxvkd") == "dairy");
  REQUIRE(allergic.at("fvjkl") == "soy");

  REQUIRE(not allergic.contains("kfcds"));
  REQUIRE(not allergic.contains("nhms"));
  REQUIRE(not allergic.contains("sbzzf"));
  REQUIRE(not allergic.contains("trh"));
}

TEST_CASE("Safe ingredients") {
  std::istringstream input{example};
  auto const foods = parse_input(input);

  auto const allergic = find_allergic_ingredients(foods);
  auto const safe = find_safe_ingredients(foods, allergic);

  REQUIRE(safe.size() == 4);

  REQUIRE(std::ranges::find(safe, "kfcds") != safe.end());
  REQUIRE(std::ranges::find(safe, "nhms") != safe.end());
  REQUIRE(std::ranges::find(safe, "sbzzf") != safe.end());
  REQUIRE(std::ranges::find(safe, "trh") != safe.end());
}
