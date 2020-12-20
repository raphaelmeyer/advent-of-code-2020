#pragma once

#include <array>
#include <istream>
#include <map>
#include <utility>
#include <vector>

using Edges = std::array<uint, 4>;

struct Tile {
  uint id;
  Edges edges;
  uint orientation;
};
using Tiles = std::vector<Tile>;

using Image = std::vector<std::string>;
using Images = std::map<uint, Image>;

std::pair<Tiles, Images> parse_input(std::istream &input);

Tiles solve_puzzle(Tiles const &tiles);
uint64_t corner_product(Tiles const &tiles);

uint puzzle_size(Tiles const &tiles);

Tile rotate(Tile const &tile);
Tile flip(Tile const &tile);

Image create_image(Images const &tiles, Tiles const &arrangement);
Image mark_monsters(Image const &image);
uint count_roughness(Image const &marked);
