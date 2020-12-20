#pragma once

#include <istream>
#include <variant>
#include <vector>

enum class Decision { Adjacent, Sight };
struct Strategy {
  Decision decision;
  uint threshold;
};

enum class Seat { Floor, Empty, Occupied };

using Row = std::vector<Seat>;
using Seats = std::vector<Row>;

Seats parse_input(std::istream &input);
Seats simulate_until_stable(Seats const &seats, Strategy strategy);
uint count_occupied(Seats const &seats);

struct NoChange {};
using SimResult = std::variant<Seats, NoChange>;

SimResult simulate(Seats const &seats, Strategy strategy);
uint count_neighbors(Seats const &seats, uint x, uint y);
uint count_seen_seats(Seats const &seats, uint x, uint y);
