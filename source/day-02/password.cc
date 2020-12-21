#include "password.h"

#include <algorithm>
#include <functional>
#include <ranges>
#include <sstream>

Passwords parse_input(std::istream &input) {
  Passwords passwords{};

  std::string line{};
  while (std::getline(input, line)) {
    passwords.push_back(line);
  }
  return passwords;
}

Config parse_config(std::string input) {
  std::istringstream iss{input};

  char delimiter{};
  char letter{};

  int minimum{};
  int maximum{};

  std::string password{};

  iss >> minimum >> delimiter >> maximum >> letter >> delimiter >> password;

  return Config{letter, minimum, maximum, password};
}

bool OldPolicy::operator()(std::string const &entry) const {
  auto const config = parse_config(entry);

  auto const count =
      std::ranges::count_if(config.password, [letter = config.letter](auto ch) {
        return ch == letter;
      });

  return (config.minimum <= count) && (count <= config.maximum);
}

bool NewPolicy::operator()(std::string const &entry) const {
  auto const config = parse_config(entry);
  if (config.password.length() < static_cast<std::size_t>(config.maximum)) {
    return false;
  }

  auto const p1 = config.minimum - 1;
  auto const p2 = config.maximum - 1;

  if (config.password[p1] == config.password[p2]) {
    return false;
  }

  return config.password[p1] == config.letter ||
         config.password[p2] == config.letter;
}
