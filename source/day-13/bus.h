#pragma once

#include <istream>
#include <string>
#include <vector>

using Timetable = std::vector<uint>;

struct Input {
  uint from;
  Timetable timetable{};
};

struct Departure {
  uint time;
  uint id;
};

Input parse_input(std::istream &input);
Departure find_bus_after(uint from, Timetable timetable);
uint calc_result(uint from, Departure departure);

uint64_t find_earliest_subsequent(Timetable timetable);

std::vector<std::string> split_string(std::string str, std::string delim);
