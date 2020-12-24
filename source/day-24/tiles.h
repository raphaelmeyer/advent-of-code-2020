#pragma once

#include <istream>
#include <map>
#include <vector>

struct Direction {
  int q;
  int r;

  bool operator==(Direction const &) const = default;
};

constexpr Direction E{1, 0};
constexpr Direction SE{0, 1};
constexpr Direction SW{-1, 1};
constexpr Direction W{-1, 0};
constexpr Direction NW{0, -1};
constexpr Direction NE{1, -1};

struct Position {
  int q;
  int r;

  auto operator<=>(Position const &) const = default;
};

enum class Side { White, Black };
inline Side operator!(Side side) {
  return side == Side::White ? Side::Black : Side::White;
}

using Steps = std::vector<Direction>;
using Instructions = std::vector<Steps>;
using Tiles = std::map<Position, Side>;

Instructions parse_input(std::istream &input);
Steps parse_steps(std::string input);

Tiles flip_tiles(Instructions const &instructions);
uint count(Tiles const &tiles, Side side);

Tiles living_art(Tiles const &tiles);

void flip_tile(Tiles &tiles, Steps const &steps);
uint count_black(Tiles const &tiles, Position const &me);

Tiles update(Tiles tiles, uint days);
