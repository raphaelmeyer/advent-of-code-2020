#include "tiles.h"

#include <algorithm>
#include <numeric>
#include <ranges>
#include <regex>

Instructions parse_input(std::istream &input) {
  Instructions instructions{};

  std::string line{};
  while (std::getline(input, line)) {
    instructions.push_back(parse_steps(line));
  }

  return instructions;
}

Steps parse_steps(std::string input) {
  std::map<std::string, Direction> static const lookup{
      {"se", SE}, {"sw", SW}, {"ne", NE}, {"nw", NW}, {"e", E}, {"w", W}};

  std::regex static const pattern{R"((se|sw|ne|nw|e|w))"};
  std::sregex_token_iterator it{input.begin(), input.end(), pattern};
  std::sregex_token_iterator end{};

  Steps steps{};

  while (it != end) {
    steps.push_back(lookup.at(*it));
    ++it;
  }

  return steps;
}

Tiles flip_tiles(Instructions const &instructions) {
  Tiles tiles{};
  for (auto steps : instructions) {
    flip_tile(tiles, steps);
  }
  return tiles;
}

uint count(Tiles const &tiles, Side side) {
  return std::ranges::count_if(
      tiles, [side](auto const &tile) { return tile.second == side; });
}

void flip_tile(Tiles &tiles, Steps const &steps) {
  auto const position = std::accumulate(
      steps.begin(), steps.end(), Position{0, 0}, [](auto pos, auto offset) {
        return Position{pos.q + offset.q, pos.r + offset.r};
      });

  if (tiles.contains(position)) {
    tiles[position] = !tiles[position];
  } else {
    tiles[position] = Side::Black;
  }
}

Tiles living_art([[maybe_unused]] Tiles const &tiles) {
  Tiles next{};

  int min_q = 0;
  int max_q = 0;
  int min_r = 0;
  int max_r = 0;

  for (auto const &tile : tiles) {
    if (tile.second == Side::Black) {

      if (tile.first.q < min_q) {
        min_q = tile.first.q;
      }
      if (tile.first.q > max_q) {
        max_q = tile.first.q;
      }
      if (tile.first.r < min_r) {
        min_r = tile.first.r;
      }
      if (tile.first.r > max_r) {
        max_r = tile.first.r;
      }

      auto const blacks = count_black(tiles, tile.first);
      if (blacks == 1 || blacks == 2) {
        next.insert(tile);
      }
    }
  }

  for (int q = min_q - 1; q <= max_q + 1; ++q) {
    for (int r = min_r - 1; r <= max_r + 1; ++r) {
      if (not tiles.contains({q, r}) || tiles.at({q, r}) == Side::White) {
        auto const blacks = count_black(tiles, {q, r});
        if (blacks == 2) {
          next.insert({{q, r}, Side::Black});
        }
      }
    }
  }

  return next;
}

uint count_black(Tiles const &tiles, Position const &me) {
  std::array<Direction, 6> static const neighbors{E, SE, SW, W, NW, NE};

  return std::ranges::count_if(neighbors, [&](auto n) {
    Position const pos{me.q + n.q, me.r + n.r};
    if (tiles.contains(pos)) {
      return tiles.at(pos) == Side::Black;
    }
    return false;
  });
}

Tiles update(Tiles tiles, uint days) {
  for (uint i = 0; i < days; ++i) {
    tiles = living_art(tiles);
  }
  return tiles;
}
