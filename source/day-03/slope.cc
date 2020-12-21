#include "slope.h"

Position Grid::move(Position position, int x, int y) const {
  return Position{position.x + x, position.y + y};
}

void Grid::parse(std::istream &input) {
  std::string line{};
  while (std::getline(input, line)) {
    rows_.push_back(line);
  }
}

std::optional<Square> Grid::square(Position position) const {
  if (position.y >= rows_.size()) {
    // return std::nullopt;
    return {};
  }

  auto const &row = rows_[position.y];
  if (row[position.x % row.length()] == '#') {
    return Square::Tree;
  }
  return Square::Empty;
}

uint64_t count_trees(Grid const &grid, std::vector<Slope> const &slopes) {
  uint64_t result = 1;

  for (auto slope : slopes) {
    uint trees = 0;
    Position position{0, 0};

    auto square = grid.square(position);
    while (square) {
      if (*square == Square::Tree) {
        ++trees;
      }
      position = grid.move(position, slope.x, slope.y);
      square = grid.square(position);
    }
    result *= trees;
  }

  return result;
}
