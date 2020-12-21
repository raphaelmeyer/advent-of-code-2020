#pragma once

#include <istream>
#include <optional>
#include <string>
#include <vector>

enum class Square { Empty, Tree };

struct Position {
  uint x;
  uint y;
};

struct Slope {
  int x;
  int y;
};

class Grid {
public:
  void parse(std::istream &input);

  Position move(Position position, int x, int y) const;
  std::optional<Square> square(Position position) const;

private:
  std::vector<std::string> rows_;
};

uint64_t count_trees(Grid const &grid, std::vector<Slope> const &slopes);
