#pragma once

#include <string>

struct Seat {
  uint row;
  uint column;
  uint id;
};

uint seat_row(std::string input);
uint seat_column(std::string input);
Seat decode_seat(std::string input);
