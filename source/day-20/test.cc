#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "jigsaw.h"

#include <sstream>

std::string const example{R"(Tile 2311:
..##.#..#.
##..#.....
#...##..#.
####.#...#
##.##.###.
##...#.###
.#.#.#..##
..#....#..
###...#.#.
..###..###

Tile 1951:
#.##...##.
#.####...#
.....#..##
#...######
.##.#....#
.###.#####
###.##.##.
.###....#.
..#.#..#.#
#...##.#..

Tile 1171:
####...##.
#..##.#..#
##.#..#.#.
.###.####.
..###.####
.##....##.
.#...####.
#.##.####.
####..#...
.....##...

Tile 1427:
###.##.#..
.#..#.##..
.#.##.#..#
#.#.#.##.#
....#...##
...##..##.
...#.#####
.#.####.#.
..#..###.#
..##.#..#.

Tile 1489:
##.#.#....
..##...#..
.##..##...
..#...#...
#####...#.
#..#.#.#.#
...#.#.#..
##.#...##.
..##.##.##
###.##.#..

Tile 2473:
#....####.
#..#.##...
#.##..#...
######.#.#
.#...#.#.#
.#########
.###.#..#.
########.#
##...##.#.
..###.#.#.

Tile 2971:
..#.#....#
#...###...
#.#.###...
##.##..#..
.#####..##
.#..####.#
#..#.#..#.
..####.###
..#.#.###.
...#.#.#.#

Tile 2729:
...#.#.#.#
####.#....
..#.#.....
....#..#.#
.##..##.#.
.#.####...
####.#.#..
##.####...
##..#.##..
#.##...##.

Tile 3079:
#.#.#####.
.#..######
..#.......
######....
####.#..#.
.#...#.##.
#.#####.##
..#.###...
..#.......
..#.###...
)"};

TEST_CASE("Example - Part I") {
  std::istringstream input{example};
  auto const [tiles, images] = parse_input(input);
  auto arrangement = solve_puzzle(tiles);

  auto const solution = corner_product(arrangement);
  REQUIRE(solution == 20899048083289);
}

TEST_CASE("Example - Part II") {
  std::istringstream input{example};
  auto const [tiles, images] = parse_input(input);
  auto arrangement = solve_puzzle(tiles);

  auto const image = create_image(images, arrangement);
  auto const marked = mark_monsters(image);
  auto const roughness = count_roughness(marked);

  REQUIRE(roughness == 273);
}

TEST_CASE("Parse Input") {
  std::istringstream input{example};

  auto const [tiles, images] = parse_input(input);

  REQUIRE(puzzle_size(tiles) == 3);

  REQUIRE(tiles.size() == 9);
  REQUIRE(tiles[2].id == 1171);
  REQUIRE(tiles[8].edges[0] == 0b1010111110);
  REQUIRE(tiles[8].edges[1] == 0b0100001000);
  REQUIRE(tiles[8].edges[2] == 0b0010111000);
  REQUIRE(tiles[8].edges[3] == 0b1001101000);

  REQUIRE(images.size() == 9);
  REQUIRE(images.contains(3079));
  REQUIRE(images.at(3079).size() == 8);
  REQUIRE(images.at(3079)[3] == "###.#..#");
}

TEST_CASE("Rotate") {
  Tile tile{1234, {0b1010111110, 0b0100001000, 0b0001110100, 0b0001011001}, 2};

  auto const rotated = rotate(tile);

  REQUIRE(rotated.edges[0] == 0b1001101000);
  REQUIRE(rotated.edges[1] == 0b1010111110);
  REQUIRE(rotated.edges[2] == 0b0001000010);
  REQUIRE(rotated.edges[3] == 0b0001110100);

  REQUIRE(rotated.orientation == 3);
}

TEST_CASE("Flip") {
  Tile tile{1234, {0b1010111110, 0b0100001000, 0b0001110100, 0b0001011001}, 0};

  auto const flipped = flip(tile);

  REQUIRE(flipped.edges[0] == 0b0111110101);
  REQUIRE(flipped.edges[1] == 0b0001011001);
  REQUIRE(flipped.edges[2] == 0b0010111000);
  REQUIRE(flipped.edges[3] == 0b0100001000);

  REQUIRE(flipped.orientation == 4);
}
