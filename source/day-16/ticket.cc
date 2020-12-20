#include "ticket.h"

#include <algorithm>
#include <numeric>
#include <ranges>
#include <regex>

#include <iostream>

namespace {
const std::regex field_pattern{
    R"re(^([\w\s]+): (\d+)-(\d+) or (\d+)-(\d+)$)re"};
const std::regex ticket_pattern{R"(\d+)"};

constexpr auto stou = [](std::string const &str) -> uint {
  return static_cast<uint>(std::stoul(str));
};
} // namespace

Data parse_input(std::istream &input) {
  std::string line{};

  Fields fields{};
  std::getline(input, line);
  while (not line.empty()) {
    fields.push_back(parse_field(line));
    std::getline(input, line);
  }

  while (line != "your ticket:") {
    std::getline(input, line);
  }
  std::getline(input, line);
  auto my_ticket = parse_ticket(line);

  while (line != "nearby tickets:") {
    std::getline(input, line);
  }

  Tickets others{};
  while (std::getline(input, line)) {
    others.push_back(parse_ticket(line));
  }

  return {fields, my_ticket, others};
}

Field parse_field(std::string input) {
  std::smatch match{};
  if (std::regex_match(input, match, field_pattern)) {
    return {match.str(1),
            {stou(match.str(2)), stou(match.str(3)), stou(match.str(4)),
             stou(match.str(5))}};
  }

  return {};
}

Ticket parse_ticket(std::string input) {
  Ticket ticket{};

  std::sregex_token_iterator it{input.begin(), input.end(), ticket_pattern};
  std::sregex_token_iterator end{};

  while (it != end) {
    ticket.push_back(stou(it->str()));
    ++it;
  }

  return ticket;
}

std::vector<uint> check_ticket(Fields const &fields, Ticket const &ticket) {
  auto invalids = std::ranges::views::filter(ticket, [&](auto value) {
    return std::ranges::none_of(fields, [value](auto &field) {
      return (field.range.from_1 <= value && value <= field.range.to_1) ||
             (field.range.from_2 <= value && value <= field.range.to_2);
    });
  });

  return {invalids.begin(), invalids.end()};
}

bool is_valid_ticket(Fields const &fields, Ticket const &ticket) {
  return std::ranges::all_of(ticket, [&](auto value) {
    return std::ranges::any_of(fields, [value](auto &field) {
      return (field.range.from_1 <= value && value <= field.range.to_1) ||
             (field.range.from_2 <= value && value <= field.range.to_2);
    });
  });
}

Tickets filter_valid_tickets(Data const &data) {
  auto valids = std::ranges::views::filter(data.others, [&](auto other) {
    return is_valid_ticket(data.fields, other);
  });
  return {valids.begin(), valids.end()};
}

uint64_t error_rate(Data const &data) {
  std::vector<uint64_t> errors{};

  for (auto &other : data.others) {
    auto const invalids = check_ticket(data.fields, other);
    std::ranges::copy(invalids, std::back_inserter(errors));
  }
  return std::accumulate(errors.begin(), errors.end(), 0ul);
}

std::map<std::string, std::set<uint>> find_candidates(Tickets const &valids,
                                                      Ticket const &my_ticket,
                                                      Fields const &fields) {

  auto const in_range = [](Range const &range, uint value) {
    return (range.from_1 <= value && value <= range.to_1) ||
           (range.from_2 <= value && value <= range.to_2);
  };

  std::map<std::string, std::set<uint>> candidates{};

  for (auto const &field : fields) {
    for (uint pos = 0; pos < my_ticket.size(); ++pos) {
      auto const &range = field.range;
      if (in_range(range, my_ticket[pos])) {
        if (std::ranges::all_of(valids, [&, pos](auto other) {
              return in_range(range, other[pos]);
            })) {
          candidates[field.name].insert(pos);
        }
      }
    }
  }

  return candidates;
}
