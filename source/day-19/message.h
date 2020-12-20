#pragma once

#include <istream>
#include <map>
#include <string>
#include <variant>
#include <vector>

using Variable = int;
using Terminal = char;

using Singular = int;

using Variables = std::pair<Variable, Variable>;
using Production = std::variant<Terminal, Variables, Singular>;
using Productions = std::vector<Production>;

using Rule = std::pair<Variable, Productions>;

using Language = std::map<Variable, Productions>;
using Messages = std::vector<std::string>;

struct Input {
  Language language;
  Messages messages;
};

Input parse_input(std::istream &input);

Rule parse_rule(std::string input);
uint count_valid(Language const &language, Messages const &messages);
bool is_valid(Language const &language, std::string input);

Language normalize(Language const &language);

Language fix_rules(Language const &language);
