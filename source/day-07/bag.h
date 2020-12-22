#pragma once

#include <istream>
#include <map>
#include <string>
#include <utility>
#include <vector>

struct Rule {
  std::string name;
  uint count;
};

using Rules = std::map<std::string, std::vector<Rule>>;

uint count_bags_containing(Rules const &rules, std::string bag);
uint count_contained_bags(Rules const &rules, std::string bag);

Rules parse_rules(std::istream &input);

std::pair<std::string, std::vector<Rule>> parse_rule(std::string rule);
