#pragma once

#include <array>
#include <istream>
#include <vector>

constexpr uint ThreeDimensional = 3;
constexpr uint FourDimensional = 4;

using Cell = std::vector<int>;
using Cells = std::vector<Cell>;

Cells parse_input(std::istream &input);
Cells lift(Cells const &world, uint dimensions);

bool is_alive(Cells const &cells, Cell position);
uint count_neighbors(Cells const &cells, Cell me);
bool is_neighbor(Cell me, Cell other);
bool survive(Cells const &cells, Cell me);
bool new_born(Cells const &cells, Cell me);
Cells find_surrounding(Cells const &cells);

Cells tick(Cells const &cells);
