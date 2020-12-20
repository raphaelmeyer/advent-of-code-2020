#pragma once

#include <istream>
#include <map>
#include <set>
#include <string>
#include <vector>

struct Range {
  uint from_1;
  uint to_1;
  uint from_2;
  uint to_2;
};

struct Field {
  std::string name;
  Range range;
};

using Fields = std::vector<Field>;
using Ticket = std::vector<uint>;
using Tickets = std::vector<Ticket>;

struct Data {
  Fields fields;
  Ticket my_ticket;
  Tickets others;
};

Data parse_input(std::istream &input);
Field parse_field(std::string input);
Ticket parse_ticket(std::string input);

std::vector<uint> check_ticket(Fields const &fields, Ticket const &ticket);
bool is_valid_ticket(Fields const &fields, Ticket const &ticket);
Tickets filter_valid_tickets(Data const &data);

uint64_t error_rate(Data const &data);

std::map<std::string, std::set<uint>> find_candidates(Tickets const &valids,
                                                      Ticket const &my_ticket,
                                                      Fields const &fields);
