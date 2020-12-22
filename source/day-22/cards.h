#pragma once

#include <deque>
#include <istream>

using Cards = std::deque<uint>;

struct Game {
  Cards one;
  Cards two;
};

Game parse_input(std::istream &input);

Game play_round(Game game);
Game play(Game game);

enum class Winner { One, Two };

Game play_recursive(Game game);
Winner play_subgame(Game game);
Game play_recursive_round(Game game);

uint64_t calculate_score(Game const &game);
