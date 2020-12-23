#include "seat.h"

#include <iostream>

int main() {
  uint max = 0;
  std::string line{};

  Seats seats{};

  while (std::getline(std::cin, line)) {
    auto const seat = decode_seat(line);
    max = std::max(seat.id, max);
    seats[{seat.row, seat.column}] = seat.id;
  }
  std::cout << "Part I : " << max << "\n";
  std::cout << "Part II : " << free_seat_id(seats) << "\n";
}