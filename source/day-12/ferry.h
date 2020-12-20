#pragma once

#include <istream>
#include <variant>
#include <vector>

enum class Direction { North, South, East, West };

struct North {
  uint distance;
};
struct South {
  uint distance;
};
struct East {
  uint distance;
};
struct West {
  uint distance;
};
struct Left {
  uint degrees;
};
struct Right {
  uint degrees;
};
struct Forward {
  uint distance;
};

using Action = std::variant<North, South, East, West, Left, Right, Forward>;

struct Position {
  int x;
  int y;
};

std::vector<Action> parse_input(std::istream &input);

Position move_ferry(std::vector<Action> const &actions,
                    Direction initial_facing);

Position move_waypoint(std::vector<Action> const &actions,
                       Position initial_waypoint);
