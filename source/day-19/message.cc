#include "message.h"

#include <algorithm>
#include <ranges>
#include <regex>
#include <stdexcept>

Input parse_input(std::istream &input) {
  std::string line{};

  Language language{};

  std::getline(input, line);
  while (not line.empty()) {
    auto rule = parse_rule(line);
    language.insert(rule);

    std::getline(input, line);
  }

  Messages messages{};
  while (std::getline(input, line)) {
    messages.push_back(line);
  }

  return {language, messages};
}

Rule parse_rule(std::string input) {
  std::regex const terminal{R"re(^(\d+): "(\w)"$)re"};
  std::regex const variables{R"(^(\d+): (\d+) (\d+)$)"};
  std::regex const double_variables{R"(^(\d+): (\d+) (\d+) \| (\d+) (\d+)$)"};
  std::regex const singular{R"(^(\d+): (\d+)$)"};
  std::regex const double_singular{R"(^(\d+): (\d+) \| (\d+)$)"};

  std::smatch match{};

  if (std::regex_match(input, match, terminal)) {
    return Rule{std::stoi(match.str(1)), {match.str(2)[0]}};

  } else if (std::regex_match(input, match, variables)) {
    return Rule{std::stoi(match.str(1)),
                {Variables{std::stoi(match.str(2)), std::stoi(match.str(3))}}};

  } else if (std::regex_match(input, match, double_variables)) {
    return Rule{std::stoi(match.str(1)),
                {Variables{std::stoi(match.str(2)), std::stoi(match.str(3))},
                 Variables{std::stoi(match.str(4)), std::stoi(match.str(5))}}};

  } else if (std::regex_match(input, match, singular)) {
    return Rule{std::stoi(match.str(1)), {std::stoi(match.str(2))}};

  } else if (std::regex_match(input, match, double_singular)) {
    return Rule{std::stoi(match.str(1)),
                {std::stoi(match.str(2)), std::stoi(match.str(3))}};
  }

  throw std::invalid_argument{input};
  return {};
}

Language normalize(Language const &language) {
  Language normalized{};

  for (auto &rule : language) {
    for (auto &production : rule.second) {
      if (std::holds_alternative<Singular>(production)) {
        if (language.contains(std::get<Singular>(production))) {
          for (auto &p : language.at(std::get<Singular>(production))) {
            normalized[rule.first].push_back(p);
          }
        }
      } else {
        normalized[rule.first].push_back(production);
      }
    }
  }

  for (auto &rule : normalized) {
    for (auto &production : rule.second) {
      if (std::holds_alternative<Singular>(production)) {
        throw std::invalid_argument{"singularity"};
      }
    }
  }

  return normalized;
}

uint count_valid(Language const &language, Messages const &messages) {
  return std::ranges::count_if(messages, [&](auto const &message) {
    return is_valid(language, message);
  });
}

bool is_valid(Language const &language, std::string input) {
  // let the input be a string I consisting of n characters: a1 ... an.
  // let the grammar contain r nonterminal symbols R1 ... Rr, with start
  // symbol R1. let P[n,n,r] be an array of booleans. Initialize all elements
  // of P to false.
  std::map<std::tuple<uint, uint, Variable>, bool> P{};

  // for each s = 1 to n
  //     for each unit production Rv → as
  //         set P[1,s,v] = true
  for (uint s = 1; s <= input.size(); ++s) {
    for (auto &rule : language) {
      P[{1, s, rule.first}] = false;
      for (auto &up : rule.second) {
        if (std::holds_alternative<Terminal>(up)) {
          if (std::get<Terminal>(up) == input[s - 1]) {
            P[{1, s, rule.first}] = true;
          }
        }
      }
    }
  }

  // for each l = 2 to n -- Length of span
  //     for each s = 1 to n-l+1 -- Start of span
  //         for each p = 1 to l-1 -- Partition of span
  //             for each production Ra    → Rb Rc
  //                 if P[p,s,b] and P[l-p,s+p,c] then set P[l,s,a] = true
  for (uint l = 2; l <= input.size(); ++l) {
    for (uint s = 1; s <= input.size() - l + 1; ++s) {
      for (uint p = 1; p <= l - 1; ++p) {
        for (auto &rule : language) {
          for (auto &r : rule.second) {
            if (std::holds_alternative<Variables>(r)) {
              auto const R = std::get<Variables>(r);
              if (P[{p, s, R.first}] && P[{l - p, s + p, R.second}]) {
                P[{l, s, rule.first}] = true;
              }
            }
          }
        }
      }
    }
  }

  Variable start = 0;

  // if P[n,1,1] is true then
  //     I is member of language
  if (P.contains({input.size(), 1, start}) && P.at({input.size(), 1, start})) {
    return true;
  }

  // else
  //     I is not member of language
  return false;
}

Language fix_rules(Language const &language) {
  Language fixed{};

  for (auto &rule : language) {
    if (rule.first == 8) {
      // 8: 42 | 42 8
      fixed.insert({8, {Singular{42}, Variables{42, 8}}});
    } else if (rule.first == 11) {
      // 11: 42 31 | 42 11 31
      // -> 11: 42 31 | 42 1000
      //    1000: 11 31
      fixed.insert({11, {Variables{42, 31}, Variables{42, 1000}}});
      fixed.insert({1000, {Variables{11, 31}}});
    } else {
      fixed.insert(rule);
    }
  }

  return fixed;
}
