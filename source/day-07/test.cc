#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "bag.h"

TEST_CASE("Parse rule with no dependency") {
  auto [color, contains] = parse_rule("faded blue bags contain no other bags.");

  REQUIRE(color == "faded blue");
  REQUIRE(contains.empty());
}

TEST_CASE("Parse rule with one dependency") {
  auto [color, contains] =
      parse_rule("vibrant plum bags contain 5 faded blue bags.");

  REQUIRE(color == "vibrant plum");
  REQUIRE(contains.size() == 1);
  REQUIRE(contains[0].name == "faded blue");
  REQUIRE(contains[0].count == 5);
}

TEST_CASE("Parse rule with more than one dependency") {
  auto [color, contains] = parse_rule(
      "dark olive bags contain 3 faded blue bags, 4 dotted black bags.");

  REQUIRE(color == "dark olive");
  REQUIRE(contains.size() == 2);
  REQUIRE(contains[0].name == "faded blue");
  REQUIRE(contains[0].count == 3);
  REQUIRE(contains[1].name == "dotted black");
  REQUIRE(contains[1].count == 4);
}

TEST_CASE("Parse rules") {

  std::string data{
      R"(light red bags contain 1 bright white bag, 2 muted yellow bags.
dark orange bags contain 3 bright white bags, 4 muted yellow bags.
bright white bags contain 1 shiny gold bag.
muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.
shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.
dark olive bags contain 3 faded blue bags, 4 dotted black bags.
vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.
faded blue bags contain no other bags.
dotted black bags contain no other bags.
)"};

  std::istringstream input{data};

  auto const rules = parse_rules(input);

  REQUIRE(rules.size() == 9);
  REQUIRE(rules.at("muted yellow").size() == 2);
  REQUIRE(rules.at("muted yellow")[0].name == "shiny gold");
  REQUIRE(rules.at("muted yellow")[0].count == 2);
  REQUIRE(rules.at("muted yellow")[1].name == "faded blue");
  REQUIRE(rules.at("muted yellow")[1].count == 9);
}

TEST_CASE("Count shiny gold combinations") {
  std::string data{
      R"(light red bags contain 1 bright white bag, 2 muted yellow bags.
dark orange bags contain 3 bright white bags, 4 muted yellow bags.
bright white bags contain 1 shiny gold bag.
muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.
shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.
dark olive bags contain 3 faded blue bags, 4 dotted black bags.
vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.
faded blue bags contain no other bags.
dotted black bags contain no other bags.
)"};

  std::istringstream input{data};

  auto const rules = parse_rules(input);

  REQUIRE(count_bags_containing(rules, "shiny gold") == 4);
}

TEST_CASE("Count contained bags") {
  std::string data{
      R"(shiny gold bags contain 2 dark red bags.
dark red bags contain 2 dark orange bags.
dark orange bags contain 2 dark yellow bags.
dark yellow bags contain 2 dark green bags.
dark green bags contain 2 dark blue bags.
dark blue bags contain 2 dark violet bags.
dark violet bags contain no other bags.
)"};

  std::istringstream input{data};

  auto const rules = parse_rules(input);

  REQUIRE(count_contained_bags(rules, "shiny gold") == 126);
}
