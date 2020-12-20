#include "ticket.h"

#include <iostream>

int main() {
  auto const data = parse_input(std::cin);
  std::cout << error_rate(data) << "\n";

  auto const valids = filter_valid_tickets(data);

  auto candidates = find_candidates(valids, data.my_ticket, data.fields);

  auto unique = [&]() {
    for (auto &candidate : candidates) {
      if (candidate.second.size() == 1) {
        return std::pair<std::string, uint>{candidate.first,
                                            *candidate.second.begin()};
      }
    }
    return std::pair<std::string, uint>{"", 0};
  };

  std::map<std::string, uint> associations{};
  while (not candidates.empty()) {
    auto [name, pos] = unique();
    if (not name.empty()) {
      associations[name] = pos;
      candidates.erase(name);
      for (auto &candidate : candidates) {
        candidate.second.erase(pos);
      }
    } else {
      throw std::out_of_range{""};
    }
  }

  uint64_t result = 1;

  for (auto const &association : associations) {
    if (association.first.starts_with("departure")) {
      result *= data.my_ticket[association.second];
    }
  }

  std::cout << result << "\n";
}
