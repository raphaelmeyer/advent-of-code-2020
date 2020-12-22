#include "bag.h"

#include <algorithm>
#include <set>
#include <sstream>
#include <stdexcept>
#include <utility>

uint count_bags_containing(Rules const &rules, std::string bag) {
  std::set<std::string> contain{};
  for (auto const &rule : rules) {
    if (std::find_if(rule.second.begin(), rule.second.end(), [bag](auto c) {
          return c.name == bag;
        }) != rule.second.end()) {
      contain.insert(rule.first);
    }
  }

  bool inserted = false;

  do {
    inserted = false;
    for (auto const &rule : rules) {
      for (auto const &contained : rule.second) {
        if (not contain.contains(rule.first)) {
          if (contain.contains(contained.name)) {
            contain.insert(rule.first);
            inserted = true;
          }
        }
      }
    }
  } while (inserted);

  return contain.size();
}

uint count_contained_bags_(Rules const &rules, std::string bag) {
  uint count = 1;
  for (auto rule : rules.at(bag)) {
    count += rule.count * count_contained_bags_(rules, rule.name);
  }
  return count;
}

uint count_contained_bags(Rules const &rules, std::string bag) {
  // remove top bag
  return count_contained_bags_(rules, bag) - 1;
}

Rules parse_rules(std::istream &input) {
  Rules rules{};

  std::string line{};
  while (std::getline(input, line)) {
    rules.insert(parse_rule(line));
  }
  return rules;
}

std::pair<std::string, std::vector<Rule>> parse_rule(std::string rule) {
  std::istringstream iss{rule};
  std::string variant{};
  std::string color{};

  iss >> variant >> color;
  auto const bag = variant + " " + color;

  auto pos = rule.find("contain");
  if (pos == std::string::npos) {
    throw std::runtime_error{"missing contain"};
  }
  pos += 7;

  std::vector<Rule> contain{};

  while (pos != std::string::npos) {
    ++pos;

    std::string number{};
    iss.str(rule.substr(pos));
    iss >> number;
    if (number == "no") {
      break;
    }

    auto const count = static_cast<uint>(std::stoul(number));
    iss >> variant >> color;
    contain.push_back({variant + " " + color, count});

    pos = rule.find(",", pos);
  }

  return {bag, contain};
}
