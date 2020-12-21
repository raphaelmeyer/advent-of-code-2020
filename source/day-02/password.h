#pragma once

#include <algorithm>
#include <ranges>
#include <string>
#include <vector>

using Passwords = std::vector<std::string>;

Passwords parse_input(std::istream &input);

struct Config {
  char letter;

  int minimum;
  int maximum;

  std::string password;
};

Config parse_config(std::string input);

struct OldPolicy {
  bool operator()(std::string const &entry) const;
};

struct NewPolicy {
  bool operator()(std::string const &entry) const;
};

template <typename Policy>
std::size_t count_valid_passwords(Passwords const &passwords) {
  return std::ranges::count_if(passwords, Policy{});
}
