#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "ticket.h"

#include <sstream>
#include <string>

std::string example{R"(class: 1-3 or 5-7
row: 6-11 or 33-44
seat: 13-40 or 45-50

your ticket:
7,1,14

nearby tickets:
7,3,47
40,4,50
55,2,20
38,6,12
)"};

TEST_CASE("Example - Part I") {
  std::istringstream input{example};
  auto const data = parse_input(input);

  REQUIRE(error_rate(data) == 71);
}

TEST_CASE("Check if ticket is valid") {
  std::istringstream input{example};
  auto const data = parse_input(input);

  auto const valid = check_ticket(data.fields, data.others[0]);
  REQUIRE(valid.empty());

  auto const invalid = check_ticket(data.fields, data.others[3]);
  REQUIRE(invalid.size() == 1);
  REQUIRE(invalid[0] == 12);
}

TEST_CASE("Parse Input") {
  std::istringstream input{example};
  auto const data = parse_input(input);

  REQUIRE(data.fields.size() == 3);
  REQUIRE(data.fields[2].name == "seat");
  REQUIRE(data.fields[2].range.from_1 == 13);
  REQUIRE(data.fields[2].range.to_1 == 40);
  REQUIRE(data.fields[2].range.from_2 == 45);
  REQUIRE(data.fields[2].range.to_2 == 50);

  REQUIRE(data.my_ticket.size() == 3);
  REQUIRE(data.my_ticket[0] == 7);
  REQUIRE(data.my_ticket[2] == 14);

  REQUIRE(data.others.size() == 4);
  REQUIRE(data.others[0].size() == 3);
  REQUIRE(data.others[0][1] == 3);
  REQUIRE(data.others[1].size() == 3);
  REQUIRE(data.others[1][2] == 50);
}

TEST_CASE("Parse Field") {
  auto const field = parse_field("row: 6-11 or 33-44");

  REQUIRE(field.name == "row");
  REQUIRE(field.range.from_1 == 6);
  REQUIRE(field.range.to_1 == 11);
  REQUIRE(field.range.from_2 == 33);
  REQUIRE(field.range.to_2 == 44);

  auto const space = parse_field("some field: 1-2 or 5-7");
  REQUIRE(space.name == "some field");
}

TEST_CASE("Parse Ticket") {
  auto const ticket = parse_ticket("55,2,20,12");

  REQUIRE(ticket.size() == 4);
  REQUIRE(ticket[0] == 55);
  REQUIRE(ticket[1] == 2);
  REQUIRE(ticket[2] == 20);
  REQUIRE(ticket[3] == 12);
}

TEST_CASE("Check if ticket is valid") {
  std::istringstream input{example};
  auto const data = parse_input(input);

  REQUIRE(is_valid_ticket(data.fields, data.others[0]));
  REQUIRE(not is_valid_ticket(data.fields, data.others[3]));
}

TEST_CASE("Discard invalid tickets") {
  std::istringstream input{example};
  auto const data = parse_input(input);

  auto valids = filter_valid_tickets(data);

  REQUIRE(valids.size() == 1);
  REQUIRE(valids[0][2] == 47);
}
