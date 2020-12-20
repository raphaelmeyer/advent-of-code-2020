#include "jigsaw.h"

#include <algorithm>
#include <cmath>
#include <functional>
#include <numeric>
#include <ranges>
#include <regex>
#include <string>

namespace {

std::optional<Tiles> backtrack(Tiles const &tiles, uint size,
                               std::vector<Tile> &solution) {

  auto const is_unused = [](std::vector<Tile> const &solution,
                            Tile const &tile) {
    auto const it = std::ranges::find_if(solution, [&tile](auto &in_solution) {
      return in_solution.id == tile.id;
    });
    return it == solution.end();
  };

  auto const fits = [&solution, size](Tile const &tile) {
    auto x = solution.size() % size;
    auto y = solution.size() / size;

    if (x > 0) {
      auto const &left = solution.back();
      if (left.edges[1] != tile.edges[3]) {
        return false;
      }
    }
    if (y > 0) {
      auto const &up = solution[x + (y - 1) * size];
      if (up.edges[2] != tile.edges[0]) {
        return false;
      }
    }

    return true;
  };

  for (auto const &tile : tiles) {
    if (is_unused(solution, tile)) {
      auto current_tile = tile;
      for (uint i = 0; i < 8; i++) {
        if (fits(current_tile)) {
          solution.push_back(current_tile);

          if (solution.size() == size * size) {
            return solution;
          }

          auto result = backtrack(tiles, size, solution);
          if (result) {
            return result;
          }
          solution.pop_back();
        }
        if (i == 3) {
          current_tile = flip(tile);
        } else {
          current_tile = rotate(current_tile);
        }
      }
    }
  }

  return {};
}

} // namespace

std::pair<Tiles, Images> parse_input(std::istream &input) {
  Tiles tiles{};
  Images images{};

  std::regex const title{R"re(^Tile (\d+):$)re"};

  std::string line{};
  while (std::getline(input, line)) {
    std::smatch match{};
    if (not std::regex_match(line, match, title)) {
      throw std::invalid_argument{line};
    }
    auto id = static_cast<uint>(std::stoul(match.str(1)));

    uint top = 0;
    uint right = 0;
    uint left = 0;
    uint bottom = 0;

    Image img{};

    for (uint i = 0; i < 10; ++i) {
      std::getline(input, line);

      // top
      if (i == 0) {
        for (auto c : line) {
          top <<= 1;
          if (c == '#') {
            top |= 1;
          }
        }
      }

      if (0 < i && i < 9) {
        img.push_back(line.substr(1, 8));
      }

      right <<= 1;
      if (line[9] == '#') {
        right |= 1;
      }
      left <<= 1;
      if (line[0] == '#') {
        left |= 1;
      }

      if (i == 9) {
        // bottom
        for (auto c : line) {
          bottom <<= 1;
          if (c == '#') {
            bottom |= 1;
          }
        }
      }
    }

    tiles.push_back(Tile{id, {top, right, bottom, left}, 0});
    images[id] = img;

    std::getline(input, line);
  }

  return {tiles, images};
}

Tiles solve_puzzle(Tiles const &tiles) {
  auto const size = puzzle_size(tiles);

  std::vector<Tile> solution{};
  auto const result = backtrack(tiles, size, solution);
  if (result) {
    return *result;
  }

  throw std::out_of_range{"no solution found"};
  return {};
}

uint64_t corner_product(Tiles const &tiles) {
  auto size = puzzle_size(tiles);
  std::vector<uint> const corners{tiles[0].id, tiles[size - 1].id,
                                  tiles[size * (size - 1)].id,
                                  tiles[size * size - 1].id};

  return std::accumulate(corners.begin(), corners.end(), 1ul,
                         std::multiplies<>());
}

uint puzzle_size(Tiles const &tiles) { return std::sqrt(tiles.size()); }

namespace {

auto const reverse = [](uint value) {
  uint reverted = 0;
  for (uint i = 0; i < 10; ++i) {
    reverted <<= 1;
    if (value & 1) {
      reverted |= 1;
    }
    value >>= 1;
  }
  return reverted;
};

} // namespace

Tile rotate(Tile const &tile) {
  return {tile.id,
          {reverse(tile.edges[3]), tile.edges[0], reverse(tile.edges[1]),
           tile.edges[2]},
          tile.orientation + 1};
}

Tile flip(Tile const &tile) {
  return {tile.id,
          {reverse(tile.edges[0]), tile.edges[3], reverse(tile.edges[2]),
           tile.edges[1]},
          tile.orientation + 4};
}

namespace {

char get_pixel(uint orientation, Image const &image, uint x, uint y) {
  auto const dim = image.size() - 1;
  switch (orientation) {
  case 0:
    return image[y][x];
  case 1:
    return image[dim - x][y];
  case 2:
    return image[dim - y][dim - x];
  case 3:
    return image[x][dim - y];
  case 4:
    return image[y][dim - x];
  case 5:
    return image[dim - x][dim - y];
  case 6:
    return image[dim - y][x];
  case 7:
    return image[x][y];
  default:
    throw std::out_of_range{"invalid orientation"};
  }
}

void set_pixel(uint orientation, Image &image, uint x, uint y, char pixel) {
  auto const dim = image.size() - 1;
  switch (orientation) {
  case 0:
    image[y][x] = pixel;
    break;
  case 1:
    image[x][dim - y] = pixel;
    break;
  case 2:
    image[dim - y][dim - x] = pixel;
    break;
  case 3:
    image[dim - x][y] = pixel;
    break;
  case 4:
    image[y][dim - x] = pixel;
    break;
  case 5:
    image[dim - x][dim - y] = pixel;
    break;
  case 6:
    image[dim - y][x] = pixel;
    break;
  case 7:
    image[x][y] = pixel;
    break;
  default:
    throw std::out_of_range{"invalid orientation"};
    break;
  }
}

} // namespace

Image create_image(Images const &images, Tiles const &arrangement) {
  auto const size = puzzle_size(arrangement) * 8;
  uint Y = 0;
  uint X = 0;

  Image image{};
  for (uint i = 0; i < size; ++i) {
    image.push_back("");
  }

  for (auto const &tile : arrangement) {
    for (uint y = 0; y < 8; ++y) {
      for (uint x = 0; x < 8; ++x) {
        auto const pixel =
            get_pixel(tile.orientation, images.at(tile.id), x, y);
        image[Y + y].push_back(pixel);
      }
    }
    X += 8;
    if (X >= size) {
      Y += 8;
      X = 0;
    }
  }

  return image;
}

Image mark_monsters(Image const &image) {
  //           1111111111
  // 01234567890123456789
  //                   #
  // #    ##    ##    ###
  //  #  #  #  #  #  #
  std::array<std::vector<uint>, 3> const monster{
      {{18}, {0, 5, 6, 11, 12, 17, 18, 19}, {1, 4, 7, 10, 13, 16}}};

  uint width = 20;
  uint height = 3;

  auto const match_monster = [&monster, &image](uint x, uint y,
                                                uint orientation) {
    for (uint j = 0; j < 3; ++j) {
      for (auto i : monster[j]) {
        if (get_pixel(orientation, image, x + i, y + j) != '#') {
          return false;
        }
      }
    }
    return true;
  };

  auto const mark_monster = [&monster](Image &marked, uint x, uint y,
                                       uint orientation) {
    for (uint j = 0; j < 3; ++j) {
      for (auto i : monster[j]) {
        set_pixel(orientation, marked, x + i, y + j, 'o');
      }
    }
  };

  for (uint orientation = 0; orientation < 8; ++orientation) {
    Image marked = image;
    bool found_monster = false;
    for (uint y = 0; y <= image.size() - height; ++y) {
      for (uint x = 0; x <= image.size() - width; ++x) {
        if (match_monster(x, y, orientation)) {
          mark_monster(marked, x, y, orientation);
          found_monster = true;
        }
      }
    }
    if (found_monster) {
      return marked;
    }
  }
  return {};
}

uint count_roughness(Image const &marked) {
  return std::accumulate(
      marked.begin(), marked.end(), 0u,
      [](auto acc, auto line) { return acc + std::ranges::count(line, '#'); });
}
