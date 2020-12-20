#include "ferry.h"

#include <string>
#include <utility>

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

std::vector<Action> parse_input(std::istream &input) {
  std::vector<Action> actions{};

  char action;
  uint value;

  while (not input.eof()) {
    input >> action >> value;
    if (input.good()) {
      switch (action) {
      case 'N': {
        actions.emplace_back(North{value});
      } break;
      case 'E': {
        actions.emplace_back(East{value});
      } break;
      case 'S': {
        actions.emplace_back(South{value});
      } break;
      case 'W': {
        actions.emplace_back(West{value});
      } break;
      case 'L': {
        actions.emplace_back(Left{value});
      } break;
      case 'R': {
        actions.emplace_back(Right{value});
      } break;
      case 'F': {
        actions.emplace_back(Forward{value});
      } break;
      default:
        break;
      }
    }
  }

  return actions;
}

Position move_ferry(std::vector<Action> const &actions,
                    Direction initial_facing) {

  Position position{0, 0};
  Direction facing = initial_facing;

  auto const left = [](auto current) {
    switch (current) {
    case Direction::North:
      return Direction::West;
    case Direction::East:
      return Direction::North;
    case Direction::South:
      return Direction::East;
    case Direction::West:
      return Direction::South;
    }
    return current;
  };

  auto const right = [](auto current) {
    switch (current) {
    case Direction::North:
      return Direction::East;
    case Direction::East:
      return Direction::South;
    case Direction::South:
      return Direction::West;
    case Direction::West:
      return Direction::North;
    }
    return current;
  };

  for (auto const action : actions) {
    std::visit(overloaded{[&](North n) { position.y += n.distance; },
                          [&](East e) { position.x += e.distance; },
                          [&](South s) { position.y -= s.distance; },
                          [&](West w) { position.x -= w.distance; },
                          [&](Left l) {
                            while (l.degrees >= 90) {
                              facing = left(facing);
                              l.degrees -= 90;
                            }
                          },
                          [&](Right r) {
                            while (r.degrees >= 90) {
                              facing = right(facing);
                              r.degrees -= 90;
                            }
                          },
                          [&](Forward f) {
                            switch (facing) {
                            case Direction::North:
                              position.y += f.distance;
                              break;
                            case Direction::East:
                              position.x += f.distance;
                              break;
                            case Direction::South:
                              position.y -= f.distance;
                              break;
                            case Direction::West:
                              position.x -= f.distance;
                              break;
                            }
                          }},
               action);
  }

  return position;
}

Position move_waypoint(std::vector<Action> const &actions,
                       Position initial_waypoint) {

  auto waypoint = initial_waypoint;
  Position position{0, 0};

  for (auto const action : actions) {
    std::visit(overloaded{[&](North n) { waypoint.y += n.distance; },
                          [&](East e) { waypoint.x += e.distance; },
                          [&](South s) { waypoint.y -= s.distance; },
                          [&](West w) { waypoint.x -= w.distance; },
                          [&](Left l) {
                            Position relative{waypoint.x - position.x,
                                              waypoint.y - position.y};
                            while (l.degrees >= 90) {
                              relative = {-relative.y, relative.x};
                              l.degrees -= 90;
                            }
                            waypoint.x = position.x + relative.x;
                            waypoint.y = position.y + relative.y;
                          },
                          [&](Right r) {
                            Position relative{waypoint.x - position.x,
                                              waypoint.y - position.y};
                            while (r.degrees >= 90) {
                              relative = {relative.y, -relative.x};
                              r.degrees -= 90;
                            }
                            waypoint.x = position.x + relative.x;
                            waypoint.y = position.y + relative.y;
                          },
                          [&](Forward f) {
                            auto x = waypoint.x - position.x;
                            auto y = waypoint.y - position.y;

                            position.x += f.distance * x;
                            position.y += f.distance * y;

                            waypoint.x = position.x + x;
                            waypoint.y = position.y + y;
                          }},
               action);
  }

  return position;
}
