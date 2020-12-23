#include "cups.h"

#include <algorithm>
#include <numeric>
#include <ranges>

Cups parse_input(std::string input, uint total) {
  std::vector<uint> labels{};
  for (auto label : input) {
    labels.push_back(label - '0');
  }

  Cups cups(labels.size() + 1);
  cups[0] = labels.front();

  for (uint i = 0; i < labels.size(); ++i) {
    cups[labels[i]] = labels[(i + 1) % labels.size()];
  }

  if (total > 9) {
    auto more = std::ranges::views::iota(11u, total + 1);
    cups.insert(cups.end(), more.begin(), more.end());
    cups.push_back(labels.front());
    cups[labels.back()] = 10;
  }

  return cups;
}

void move(Cups &cups) {
  auto constexpr minus_one = [](auto label, auto size) {
    return label > 1 ? label - 1 : size;
  };

  auto const max = cups.size() - 1;
  auto current = cups[0];

  // pick 3
  auto pick3 = cups[cups[0]];
  cups[cups[0]] = cups[cups[cups[pick3]]];

  // select destination
  auto destination = minus_one(current, max);
  while (destination == pick3 || destination == cups[pick3] ||
         destination == cups[cups[pick3]]) {
    destination = minus_one(destination, max);
  }

  // insert pick after destination
  cups[cups[cups[pick3]]] = cups[destination];
  cups[destination] = pick3;

  // next current
  cups[0] = cups[cups[0]];
}

void make_moves(Cups &cups, uint times) {
  for (uint i = 0; i < times; ++i) {
    move(cups);
  }
}

std::string print_after(Cups cups, uint label) {
  std::string result{};
  for (uint i = cups[label]; i != label; i = cups[i]) {
    result += std::to_string(i);
  }
  return result;
}

std::pair<uint, uint> pair_after(Cups cups, uint label) {
  return {cups[label], cups[cups[label]]};
}

int64_t calc_result(uint one, uint two) {
  return static_cast<int64_t>(one) * static_cast<int64_t>(two);
}
