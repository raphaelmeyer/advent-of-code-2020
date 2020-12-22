#include "passport.h"

#include <algorithm>
#include <functional>
#include <map>
#include <ranges>
#include <set>
#include <sstream>

using Fields = std::map<std::string, std::string>;
using Validators = std::map<std::string, std::function<bool(std::string)>>;

// Part One
Validators validators_one{
    {"byr", [](auto) { return true; }}, {"iyr", [](auto) { return true; }},
    {"eyr", [](auto) { return true; }}, {"hgt", [](auto) { return true; }},
    {"hcl", [](auto) { return true; }}, {"ecl", [](auto) { return true; }},
    {"pid", [](auto) { return true; }}};

constexpr auto number_range = [](auto value, uint from, uint to) {
  try {
    auto const number = std::stoul(value);
    return from <= number && number <= to;
  } catch (std::exception const &) {
    return false;
  }
};

constexpr auto year_range = [](auto value, uint from, uint to) {
  if (value.length() != 4) {
    return false;
  }
  return number_range(value, from, to);
};

const std::set<std::string> eye_colors{"amb", "blu", "brn", "gry",
                                       "grn", "hzl", "oth"};

// Part Two
Validators validators_two{
    {"byr", [](auto value) { return year_range(value, 1920, 2020); }},
    {"iyr", [](auto value) { return year_range(value, 2010, 2020); }},
    {"eyr", [](auto value) { return year_range(value, 2020, 2030); }},
    {"hgt",
     [](auto value) {
       if (value.ends_with("cm")) {
         return number_range(value.substr(0, value.find("cm")), 150, 193);
       }
       if (value.ends_with("in")) {
         return number_range(value.substr(0, value.find("in")), 59, 76);
       }
       return false;
     }},
    {"hcl",
     [](auto value) {
       if (value.length() != 7) {
         return false;
       }
       if (value.front() != '#') {
         return false;
       }
       return std::ranges::all_of(value.substr(1), ::isxdigit);
     }},
    {"ecl", [](auto value) { return eye_colors.contains(value); }},
    {"pid", [](auto value) {
       if (value.length() != 9) {
         return false;
       }
       return std::ranges::all_of(value, ::isdigit);
     }}};

bool validate_fields(Fields const &fields, Version version) {
  auto const validators =
      (version == Version::One) ? validators_one : validators_two;

  for (auto validator : validators) {
    if (not fields.contains(validator.first)) {
      return false;
    }
    if (not validator.second(fields.at(validator.first))) {
      return false;
    }
  }
  return true;
}

Fields parse_passport(std::string data) {
  Fields fields{};

  std::istringstream iss{data};
  std::string key_value;
  while (iss >> key_value) {
    if (key_value.length() > 3) {
      fields[key_value.substr(0, 3)] = key_value.substr(4);
    }
  }
  return fields;
}

bool is_valid_passport(std::string data, Version version) {
  auto const fields = parse_passport(data);
  return validate_fields(fields, version);
}

std::vector<std::string> parse_input(std::istream &input) {
  std::vector<std::string> items{};

  std::string line{};
  while (std::getline(input, line)) {
    auto data = line;
    while (std::getline(input, line) && not line.empty()) {
      data += " " + line;
    }
    if (not data.empty()) {
      items.push_back(data);
    }
  }
  return items;
}

uint count_valid_passports(std::vector<std::string> const &passport_data,
                           Version version) {
  uint valid_passports = 0;
  for (auto data : passport_data) {
    if (is_valid_passport(data, version)) {
      ++valid_passports;
    }
  }

  return valid_passports;
}
