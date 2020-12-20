#include "jolt.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <ranges>

std::vector<uint> parse_input(std::istream &input) {
  std::vector<uint> adapters{};
  while (not input.eof()) {
    uint64_t value = 0;
    input >> value;
    if (input.good()) {
      adapters.push_back(value);
    }
  }
  return adapters;
}

Diffs connect_jolt_adapters(std::vector<uint> const &adapters) {
  auto sorted = adapters;
  std::ranges::sort(sorted);

  auto const device = sorted.back() + 3;
  sorted.push_back(device);

  std::vector<uint> jolt_diff{};
  std::adjacent_difference(sorted.begin(), sorted.end(),
                           std::back_inserter(jolt_diff));

  return {static_cast<uint>(std::ranges::count(jolt_diff, 1)),
          static_cast<uint>(std::ranges::count(jolt_diff, 2)),
          static_cast<uint>(std::ranges::count(jolt_diff, 3))};
}

uint64_t jolt_permutations(std::vector<uint> const &adapters) {
  auto sorted = adapters;
  std::ranges::sort(sorted);

  auto const device = sorted.back() + 3;
  sorted.push_back(device);

  std::vector<uint> jolt_diff{};
  std::adjacent_difference(sorted.begin(), sorted.end(),
                           std::back_inserter(jolt_diff));

  std::map<uint, uint> seqs{};
  uint len = 0;

  for (auto diff : jolt_diff) {
    if (diff == 1) {
      len++;
    } else {
      if (len > 0) {
        seqs[len]++;
        len = 0;
      }
    }
  }

  uint64_t count = 1;
  for (auto seq : seqs) {
    auto seq_count = count_permutations(seq.first);
    count *= std::pow(seq_count, seq.second);

    std::cout << seq.second << " x length of " << seq.first << " -> "
              << seq_count << "\n";
  }

  return count;
}

bool valid_(std::vector<uint> const &current) {
  std::vector<uint> diffs{};
  std::adjacent_difference(current.begin(), current.end(),
                           std::back_inserter(diffs));
  return std::ranges::all_of(diffs, [](auto v) { return v <= 3; });
}

uint64_t count_(uint pos, std::vector<uint> current, uint length) {
  if (pos > length) {
    current.push_back(length + 3);
    return valid_(current) ? 1 : 0;
  }

  if (not valid_(current)) {
    return 0;
  }

  current.push_back(pos);
  auto count = count_(pos + 1, current, length);

  current.pop_back();
  count += count_(pos + 1, current, length);

  return count;
}

uint64_t count_permutations(uint length) {
  auto const count = count_(1, {}, length);

  return count;
}
