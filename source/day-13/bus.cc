#include "bus.h"

#include <algorithm>
#include <ranges>

Input parse_input(std::istream &input) {
  std::string line{};
  std::getline(input, line);
  uint from = std::stoul(line);

  Timetable timetable{};

  std::getline(input, line);
  for (auto id : split_string(line, ",")) {
    if (id == "x") {
      timetable.push_back(0);
    } else {
      timetable.push_back(std::stoul(id));
    }
  }

  return {from, timetable};
}

Departure find_bus_after(uint from, Timetable timetable) {
  std::vector<Departure> departures{};

  for (auto bus : timetable) {
    if (bus != 0) {
      auto time = bus;
      while (time < from) {
        time += bus;
      }
      departures.emplace_back(time, bus);
    }
  }

  return *std::ranges::min_element(
      departures, [](auto a, auto b) { return a.time < b.time; });
}

uint calc_result(uint from, Departure departure) {
  return (departure.time - from) * departure.id;
}

uint64_t find_earliest_subsequent(Timetable timetable) {
  struct Bus {
    uint id;
    uint offset;
  };

  std::vector<Bus> buses{};

  for (uint i = 0; i < timetable.size(); ++i) {
    if (timetable[i] != 0) {
      buses.emplace_back(timetable[i], i);
    }
  }

  std::ranges::sort(buses, [](auto a, auto b) { return a.id < b.id; });
  std::ranges::reverse(buses);

  auto it = buses.begin();
  uint64_t n = it->id;

  // id - offset (mod id)
  uint64_t x = it->id;
  while (x < it->offset) {
    x += it->id;
  };
  x -= it->offset;
  x %= it->id;

  ++it;
  while (it != buses.end()) {
    auto n_next = it->id;

    // id - offset (mod id)
    auto a_next = it->id;
    while (a_next < it->offset) {
      a_next += it->id;
    }
    a_next -= it->offset;
    a_next %= it->id;

    while (x % n_next != a_next) {
      x += n;
    }

    n *= n_next;
    ++it;
  }

  return x;
}

std::vector<std::string> split_string(std::string str, std::string delim) {
  std::vector<std::string> result{};
  std::string_view rest{str};

  auto pos = rest.find(delim);
  while (pos != std::string::npos) {
    result.emplace_back(rest.substr(0, pos));
    rest = rest.substr(pos + delim.length());
    pos = rest.find(delim);
  }
  result.emplace_back(rest);

  return result;
}
