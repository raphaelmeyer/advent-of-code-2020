#include "seats.h"

#include <algorithm>
#include <numeric>
#include <ranges>
#include <utility>

Seats parse_input(std::istream &input) {
  Seats seats{};
  std::string line{};
  while (std::getline(input, line)) {
    Row row{};
    for (auto c : line) {
      row.push_back(c == 'L' ? Seat::Empty : Seat::Floor);
    }
    seats.push_back(row);
  }
  return seats;
}

Seats simulate_until_stable(Seats const &seats, Strategy strategy) {
  auto prev = seats;
  std::variant<Seats, NoChange> result{};

  for (;;) {
    result = simulate(prev, strategy);
    if (auto end = std::get_if<NoChange>(&result); end) {
      return prev;
    } else if (auto next = std::get_if<Seats>(&result); next) {
      prev = *next;
    }
  }

  return {};
}

uint count_occupied(Seats const &seats) {
  return std::accumulate(seats.begin(), seats.end(), 0,
                         [](auto acc, auto const &row) {
                           return acc + std::ranges::count(row, Seat::Occupied);
                         });
}

SimResult simulate(Seats const &seats, Strategy strategy) {
  Seats next{};
  bool has_changed = false;

  for (uint y = 0; y < seats.size(); ++y) {
    Row row{};
    for (uint x = 0; x < seats[y].size(); ++x) {
      if (seats[y][x] == Seat::Floor) {
        row.push_back(Seat::Floor);
      } else {
        auto const neighbors = strategy.decision == Decision::Adjacent
                                   ? count_neighbors(seats, x, y)
                                   : count_seen_seats(seats, x, y);
        if (seats[y][x] == Seat::Empty) {
          if (neighbors == 0) {
            has_changed = true;
            row.push_back(Seat::Occupied);
          } else {
            row.push_back(Seat::Empty);
          }
        } else if (seats[y][x] == Seat::Occupied) {
          if (neighbors < strategy.threshold) {
            row.push_back(Seat::Occupied);
          } else {
            has_changed = true;
            row.push_back(Seat::Empty);
          }
        }
      }
    }
    next.push_back(row);
  }

  if (not has_changed) {
    return NoChange{};
  }

  return next;
}

uint count_neighbors(Seats const &seats, uint x, uint y) {
  auto from_y = y == 0 ? 0 : y - 1;
  auto to_y = y + 1 < seats.size() ? y + 1 : y;

  auto from_x = x == 0 ? 0 : x - 1;
  auto to_x = x + 1 < seats[y].size() ? x + 1 : x;

  uint count = 0;

  for (uint i = from_y; i <= to_y; ++i) {
    for (uint j = from_x; j <= to_x; ++j) {
      if (j != x || i != y) {
        if (seats[i][j] == Seat::Occupied) {
          ++count;
        }
      }
    }
  }
  return count;
}

uint count_seen_seats(Seats const &seats, uint x, uint y) {

  struct Move {
    int dx;
    int dy;
  };

  std::vector<Move> moves{{-1, -1}, {0, -1}, {1, -1}, {-1, 0},
                          {1, 0},   {-1, 1}, {0, 1},  {1, 1}};

  auto const valid = [&seats](auto move, auto x, auto y) {
    if (move.dy < 0 && y == 0) {
      return false;
    }
    if (move.dy > 0 && y + 1 >= seats.size()) {
      return false;
    }
    if (move.dx < 0 && x == 0) {
      return false;
    }
    if (move.dx > 0 && x + 1 >= seats[y + move.dy].size()) {
      return false;
    }
    return true;
  };

  return std::ranges::count_if(moves, [&](auto move) {
    auto i = x;
    auto j = y;
    while (valid(move, i, j)) {
      i += move.dx;
      j += move.dy;
      if (seats[j][i] == Seat::Empty) {
        return false;
      }
      if (seats[j][i] == Seat::Occupied) {
        return true;
      }
    }
    return false;
  });
}
