#pragma once

#include <map>
#include <string>
#include <utility>

struct Seat {
  uint row;
  uint column;
  uint id;
};

using Seats = std::map<std::pair<uint, uint>, uint>;

uint seat_row(std::string input);
uint seat_column(std::string input);
Seat decode_seat(std::string input);

uint free_seat_id(Seats const &seats);
