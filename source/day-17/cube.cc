#include "cube.h"

#include <algorithm>
#include <array>
#include <numeric>
#include <ranges>

Cells generate_(uint dimensions) {
  const std::vector<int> I{-1, 0, 1};

  if (dimensions < 2) {
    return {{-1}, {0}, {1}};
  }

  auto cells = generate_(dimensions - 1);
  Cells result{};

  for (auto i : I) {
    for (auto cell : cells) {
      cell.push_back(i);
      result.push_back(cell);
    }
  }

  return result;
}

Cells generate_relative_neighbors(uint dimensions) {
  auto cells = generate_(dimensions);
  auto me = std::ranges::find_if(cells, [](auto cell) {
    return std::ranges::all_of(cell, [](auto x) { return x == 0; });
  });

  if (me != cells.end()) {
    cells.erase(me);
  }

  return cells;
}

std::array<Cells, 5> const relative_neighbors{{{},
                                               {},
                                               {},
                                               generate_relative_neighbors(3),
                                               generate_relative_neighbors(4)}};

Cells parse_input(std::istream &input) {
  Cells cells{};

  int y = 0;
  std::string line{};
  while (std::getline(input, line)) {
    int x = 0;
    for (auto cell : line) {
      if (cell == '#') {
        cells.push_back(Cell{x, y});
      }
      ++x;
    }
    ++y;
  }

  return cells;
}

Cells lift(Cells const &world, uint dimensions) {
  Cells lifted{};
  std::ranges::transform(world, std::back_inserter(lifted),
                         [dimensions](auto const &cell) {
                           Cell lifted{cell};
                           lifted.insert(lifted.end(), dimensions - 2, 0);
                           return lifted;
                         });

  return lifted;
}

bool is_alive(Cells const &cells, Cell position) {
  return std::ranges::find(cells, position) != cells.end();
}

uint count_neighbors(Cells const &cells, Cell me) {
  return std::ranges::count_if(
      cells, [me](auto cell) { return is_neighbor(me, cell); });
}

bool is_neighbor(Cell me, Cell other) {
  return me != other &&
         std::inner_product(
             me.begin(), me.end(), other.begin(), true,
             [](bool acc, bool match) { return acc && match; },
             [](auto a, auto b) { return std::abs(a - b) <= 1; });
}

bool survive(Cells const &cells, Cell me) {
  auto const neighbors = count_neighbors(cells, me);
  return neighbors == 2 || neighbors == 3;
}

bool new_born(Cells const &cells, Cell me) {
  auto const neighbors = count_neighbors(cells, me);
  return neighbors == 3;
}

Cells find_surrounding(Cells const &cells) {
  Cells surrounding{};

  for (auto cell : cells) {
    for (auto neighbor : relative_neighbors[cell.size()]) {
      Cell candidate{};
      auto a = cell.begin();
      auto b = neighbor.begin();
      while (a != cell.end()) {
        candidate.push_back(*a + *b);
        ++a;
        ++b;
      }
      if (std::ranges::find(surrounding, candidate) == surrounding.end() &&
          (not is_alive(cells, candidate))) {
        surrounding.push_back(candidate);
      }
    }
  }

  return surrounding;
}

Cells tick(Cells const &cells) {
  Cells next{};

  for (auto cell : cells) {
    if (survive(cells, cell)) {
      next.push_back(cell);
    }
  }

  auto const surroundings = find_surrounding(cells);
  for (auto surrounding : surroundings) {
    if (new_born(cells, surrounding)) {
      next.push_back(surrounding);
    }
  }

  return next;
}
