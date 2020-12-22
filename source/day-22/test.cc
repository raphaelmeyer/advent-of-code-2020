#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "cards.h"

#include <sstream>

std::string const example{R"(Player 1:
9
2
6
3
1

Player 2:
5
8
4
7
10
)"};

TEST_CASE("Example - Part I") {
  std::istringstream input{example};
  auto game = parse_input(input);

  game = play(game);

  REQUIRE(calculate_score(game) == 306);
}

TEST_CASE("Example - Part II") {
  std::istringstream input{example};
  auto game = parse_input(input);

  game = play_recursive(game);

  REQUIRE(calculate_score(game) == 291);
}

TEST_CASE("Parse Input") {
  std::istringstream input{example};
  auto game = parse_input(input);

  REQUIRE(game.one.size() == 5);
  REQUIRE(game.one.front() == 9);
  REQUIRE(game.one.back() == 1);

  REQUIRE(game.two.size() == 5);
  REQUIRE(game.two.front() == 5);
  REQUIRE(game.two.back() == 10);
}

TEST_CASE("Play round, player two wins") {
  Game game{{1, 2, 3, 4, 5}, {7, 6, 9}};

  game = play_round(game);

  REQUIRE(game.one.size() == 4);
  REQUIRE(game.one.front() == 2);
  REQUIRE(game.one.back() == 5);

  REQUIRE(game.two.size() == 4);
  REQUIRE(game.two[0] == 6);
  REQUIRE(game.two[2] == 7);
  REQUIRE(game.two[3] == 1);
}

TEST_CASE("Play round, player one wins") {
  Game game{{9, 2, 3, 4, 5}, {7, 6, 1}};

  game = play_round(game);

  REQUIRE(game.one.size() == 6);
  REQUIRE(game.one[0] == 2);
  REQUIRE(game.one[4] == 9);
  REQUIRE(game.one[5] == 7);

  REQUIRE(game.two.size() == 2);
  REQUIRE(game.two.front() == 6);
  REQUIRE(game.two.back() == 1);
}

TEST_CASE("Play until one player is out of cards") {
  Game game{{9, 3, 5}, {7, 1}};

  game = play(game);

  REQUIRE((game.one.size() == 0 || game.two.size() == 0));
  REQUIRE((game.one.size() == 5 || game.two.size() == 5));
}

TEST_CASE("Calculate score") {
  Game game{{3, 2, 10, 6, 8, 5, 9, 4, 7, 1}, {}};

  auto const score = calculate_score(game);
  REQUIRE(score == 306);
}

TEST_CASE("Calculate score when player two wins") {
  Game game{{}, {3, 2, 10, 6, 8, 5, 9, 4, 7, 1}};

  auto const score = calculate_score(game);
  REQUIRE(score == 306);
}

TEST_CASE("Prevent infinite loop") {
  Game game{{43, 19}, {2, 29, 14}};

  auto winner = play_subgame(game);
  REQUIRE(winner == Winner::One);
}

TEST_CASE("As in regular combat") {
  Game game{{9, 2, 6, 3, 1}, {5, 8, 4, 7, 10}};

  game = play_recursive_round(game);

  REQUIRE(game.one.size() == 6);
  REQUIRE(game.two.size() == 4);

  REQUIRE(game.one.front() == 2);
  REQUIRE(game.one.back() == 5);

  REQUIRE(game.two.front() == 8);
  REQUIRE(game.two.back() == 10);

  game = play_recursive_round(game);

  REQUIRE(game.one.size() == 5);
  REQUIRE(game.two.size() == 5);

  REQUIRE(game.one.front() == 6);
  REQUIRE(game.one.back() == 5);

  REQUIRE(game.two.front() == 4);
  REQUIRE(game.two.back() == 2);
}

TEST_CASE("Win subgame") {
  Game game{{4, 9, 8, 5, 2}, {3, 10, 1, 7, 6}};

  game = play_recursive_round(game);

  REQUIRE(game.one.size() == 4);
  REQUIRE(game.two.size() == 6);

  REQUIRE(game.one.front() == 9);
  REQUIRE(game.one.back() == 2);

  REQUIRE(game.two.front() == 10);
  REQUIRE(game.two.back() == 4);
}
