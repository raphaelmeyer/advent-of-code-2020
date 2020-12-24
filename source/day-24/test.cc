#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "tiles.h"

std::string const example{R"(sesenwnenenewseeswwswswwnenewsewsw
neeenesenwnwwswnenewnwwsewnenwseswesw
seswneswswsenwwnwse
nwnwneseeswswnenewneswwnewseswneseene
swweswneswnenwsewnwneneseenw
eesenwseswswnenwswnwnwsewwnwsene
sewnenenenesenwsewnenwwwse
wenwwweseeeweswwwnwwe
wsweesenenewnwwnwsenewsenwwsesesenwne
neeswseenwwswnwswswnw
nenwswwsewswnenenewsenwsenwnesesenew
enewnwewneswsewnwswenweswnenwsenwsw
sweneswneswneneenwnewenewwneswswnese
swwesenesewenwneswnwwneseswwne
enesenwswwswneneswsenwnewswseenwsese
wnwnesenesenenwwnenwsewesewsesesew
nenewswnwewswnenesenwnesewesw
eneswnwswnwsenenwnwnwwseeswneewsenese
neswnwewnwnwseenwseesewsenwsweewe
wseweeenwnesenwwwswnew
)"};

TEST_CASE("Example - Part I") {
  std::istringstream input{example};

  auto instruction = parse_input(input);
  auto tiles = flip_tiles(instruction);
  auto const black = count(tiles, Side::Black);
  REQUIRE(black == 10);
}

TEST_CASE("Example - Part II") {
  std::istringstream input{example};

  auto instruction = parse_input(input);
  auto tiles = flip_tiles(instruction);

  auto pattern = update(tiles, 100);

  REQUIRE(count(pattern, Side::Black) == 2208);
}

TEST_CASE("Parse steps") {
  REQUIRE(parse_steps("ee") == Steps{E, E});
  REQUIRE(parse_steps("ww") == Steps{W, W});
  REQUIRE(parse_steps("see") == Steps{SE, E});
  REQUIRE(parse_steps("nww") == Steps{NW, W});
  REQUIRE(parse_steps("eseswwnwne") == Steps{E, SE, SW, W, NW, NE});
}

TEST_CASE("Flip untouched tile to black") {
  Tiles tiles{};

  flip_tile(tiles, {E, NE});

  REQUIRE(tiles.contains(Position{2, -1}));
  REQUIRE(tiles.at(Position{2, -1}) == Side::Black);
}

TEST_CASE("Flip white tile to black") {
  Tiles tiles{{{-1, 2}, Side::White}};

  flip_tile(tiles, {SE, SW});

  REQUIRE(tiles.at(Position{-1, 2}) == Side::Black);
}

TEST_CASE("Flip black tile to white") {
  Tiles tiles{{{-3, 2}, Side::Black}};

  flip_tile(tiles, {SW, W, SW});

  REQUIRE(tiles.at(Position{-3, 2}) == Side::White);
}

TEST_CASE("Flip tiles") {
  Instructions const instructions{{NE, SW}, {E, SE, E}, {W}, {SE, E, E}};

  auto const tiles = flip_tiles(instructions);

  REQUIRE(tiles.contains({0, 0}));
  REQUIRE(tiles.at({0, 0}) == Side::Black);

  REQUIRE(tiles.contains({2, 1}));
  REQUIRE(tiles.at({2, 1}) == Side::White);

  REQUIRE(tiles.contains({-1, 0}));
  REQUIRE(tiles.at({-1, 0}) == Side::Black);
}

TEST_CASE(
    "Living art - black tile with zero black neighbors is flipped to white") {
  Tiles tiles{{{2, 1}, Side::Black}};

  tiles = living_art(tiles);

  if (tiles.contains({2, 1})) {
    REQUIRE(tiles.at({2, 1}) == Side::White);
  }
}

TEST_CASE("Living art - black tile with more than two black neighbors is "
          "flipped to white") {
  Tiles tiles{{{2, 1}, Side::Black},
              {{3, 0}, Side::Black},
              {{2, 2}, Side::Black},
              {{1, 1}, Side::Black}};

  tiles = living_art(tiles);

  if (tiles.contains({2, 1})) {
    REQUIRE(tiles.at({2, 1}) == Side::White);
  }
}

TEST_CASE("Living art - black tile with one black neighbor stays black") {
  Tiles tiles{{{2, 1}, Side::Black}, {{2, 0}, Side::Black}};

  tiles = living_art(tiles);

  REQUIRE(tiles.contains({2, 1}));
  REQUIRE(tiles.at({2, 1}) == Side::Black);
}

TEST_CASE("Living art - black tile with two black neighbors stays black") {
  Tiles tiles{
      {{2, 1}, Side::Black}, {{2, 0}, Side::Black}, {{2, 2}, Side::Black}};

  tiles = living_art(tiles);

  REQUIRE(tiles.contains({2, 1}));
  REQUIRE(tiles.at({2, 1}) == Side::Black);
}

TEST_CASE("Living art - white tile with exactly 2 black neighbors is flipped "
          "to black") {
  Tiles tiles{
      {{2, 1}, Side::White}, {{2, 0}, Side::Black}, {{2, 2}, Side::Black}};

  tiles = living_art(tiles);

  REQUIRE(tiles.contains({2, 1}));
  REQUIRE(tiles.at({2, 1}) == Side::Black);
}

TEST_CASE("Living art - empty tile with exactly 2 black neighbors is flipped "
          "to black") {
  Tiles tiles{{{2, 0}, Side::Black}, {{2, 2}, Side::Black}};

  tiles = living_art(tiles);

  REQUIRE(tiles.contains({2, 1}));
  REQUIRE(tiles.at({2, 1}) == Side::Black);
}
