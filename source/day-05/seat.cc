#include "seat.h"

#include <numeric>
#include <stdexcept>

uint seat_row(std::string input) {
  uint row = 0;
  for (auto letter : input.substr(0, 7)) {
    row <<= 1;
    if (letter == 'B') {
      row += 1;
    }
  }
  return row;
}

uint seat_column(std::string input) {
  uint column = 0;
  for (auto letter : input.substr(7, 3)) {
    column <<= 1;
    if (letter == 'R') {
      column += 1;
    }
  }
  return column;
}

Seat decode_seat(std::string input) {
  Seat seat{};
  seat.row = seat_row(input);
  seat.column = seat_column(input);
  seat.id = 8 * seat.row + seat.column;
  return seat;
}

uint free_seat_id(Seats const &seats) {
  for (uint row = 0; row < 128; ++row) {
    for (uint column = 0; column < 8; ++column) {
      if (not seats.contains({row, column})) {
        if (seats.contains({row - 1, column}) &&
            seats.contains({row + 1, column})) {
          return 8 * row + column;
        }
      }
    }
  }
  throw std::domain_error{""};
  return 0;
}
