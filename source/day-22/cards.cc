#include "cards.h"

#include <algorithm>
#include <numeric>
#include <ranges>
#include <string>

Game parse_input(std::istream &input) {
  Game game{};

  auto const stou = [](std::string str) {
    return static_cast<uint>(std::stoul(str));
  };

  std::string line{};
  std::getline(input, line);
  while (std::getline(input, line) && not line.empty()) {
    game.one.push_back(stou(line));
  }

  std::getline(input, line);
  while (std::getline(input, line)) {
    game.two.push_back(stou(line));
  }

  return game;
}

Game play_round(Game game) {
  if (game.one.front() > game.two.front()) {
    game.one.push_back(game.one.front());
    game.one.push_back(game.two.front());
  } else {
    game.two.push_back(game.two.front());
    game.two.push_back(game.one.front());
  }

  game.one.pop_front();
  game.two.pop_front();

  return game;
}

Game play(Game game) {
  while (game.one.size() > 0 && game.two.size() > 0) {
    game = play_round(game);
  }
  return game;
}

Game play_recursive(Game game) {
  auto history = game;
  uint period = 32;
  uint count = 0;
  while (game.one.size() > 0 && game.two.size() > 0) {
    game = play_recursive_round(game);
    if (history.one == game.one && history.two == game.two) {
      game.two.clear();
      return game;
    }
    ++count;
    if (count > period) {
      count = 0;
      period <<= 1;
      history = game;
    }
  }
  return game;
}

Winner play_subgame(Game game) {
  game = play_recursive(game);
  if (game.one.empty()) {
    return Winner::Two;
  }
  return Winner::One;
}

Game play_recursive_round(Game game) {
  auto one = game.one.front();
  auto two = game.two.front();

  game.one.pop_front();
  game.two.pop_front();

  Winner winner{};

  if (one <= game.one.size() && two <= game.two.size()) {
    Cards cards_one{};
    Cards cards_two{};
    std::ranges::copy_n(game.one.begin(), one, std::back_inserter(cards_one));
    std::ranges::copy_n(game.two.begin(), two, std::back_inserter(cards_two));
    winner = play_subgame({cards_one, cards_two});
  } else {
    winner = (one > two) ? Winner::One : Winner::Two;
  }

  if (winner == Winner::One) {
    game.one.push_back(one);
    game.one.push_back(two);
  } else {
    game.two.push_back(two);
    game.two.push_back(one);
  }

  return game;
}

uint64_t calculate_score(Game const &game) {
  auto &cards = (game.one.size() > 0) ? game.one : game.two;

  auto points = std::ranges::views::iota(1u, cards.size() + 1) |
                std::ranges::views::reverse;

  return std::inner_product(cards.begin(), cards.end(), points.begin(), 0ul);
}
