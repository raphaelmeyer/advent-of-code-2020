#include <iostream>
#include <map>
#include <numeric>
#include <utility>

#include "seat.h"

int main() {
  uint max = 0;
  std::string line{};

  std::map<std::pair<uint, uint>, uint> seats{};

  while (std::getline(std::cin, line)) {
    auto const seat = decode_seat(line);
    max = std::max(seat.id, max);
    seats[{seat.row, seat.column}] = seat.id;
  }
  std::cout << max << "\n";

  for (uint row = 0; row < 128; ++row) {
    for (uint column = 0; column < 8; ++column) {
      if (not seats.contains({row, column})) {
        if (seats.contains({row - 1, column}) &&
            seats.contains({row + 1, column})) {
          std::cout << "free seat id = " << 8 * row + column << "\n";
        }
      }
    }
  }
}