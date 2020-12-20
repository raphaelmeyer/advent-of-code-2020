#include "xmas.h"

#include <algorithm>
#include <map>
#include <numeric>

std::vector<uint64_t> parse_input(std::istream &input) {
  std::vector<uint64_t> values{};
  while (not input.eof()) {
    uint64_t value = 0;
    input >> value;
    if (input.good()) {
      values.push_back(value);
    }
  }
  return values;
}

uint64_t find_weakness(uint preamble, std::vector<uint64_t> const &values) {
  std::map<uint64_t, std::vector<uint64_t>> sums{};

  for (uint i = 0; i < values.size(); ++i) {
    for (uint j = i + 1; j < values.size() && j < i + preamble; ++j) {
      auto const sum = values[i] + values[j];
      for (uint k = j + 1; k <= i + preamble && k < values.size(); ++k) {
        sums[k].push_back(sum);
      }
    }
  }

  for (uint i = preamble; i < values.size(); ++i) {
    if (std::find(sums[i].begin(), sums[i].end(), values[i]) == sums[i].end()) {
      return values[i];
    }
  }

  return 0;
}

uint64_t break_weakness(uint64_t weak, std::vector<uint64_t> const &values) {

  for (auto it = values.begin(); it != values.end(); ++it) {
    for (auto jt = it + 2; jt != values.end(); ++jt) {
      auto const sum = std::accumulate(it, jt, 0ull);
      if (sum == weak) {
        auto const p = std::minmax_element(it, jt);
        return *p.first + *p.second;
      }
    }
  }
  return 0;
}
