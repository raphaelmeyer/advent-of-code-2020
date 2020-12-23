#include "seats.h"

#include <iostream>

int main() {
  auto const seats = parse_input(std::cin);
  auto const adj_seats = simulate_until_stable(seats, {Decision::Adjacent, 4});
  auto const adj_occupied = count_occupied(adj_seats);
  std::cout << "Part I : " << adj_occupied << "\n";

  auto const sight_seats = simulate_until_stable(seats, {Decision::Sight, 5});
  auto const sight_occupied = count_occupied(sight_seats);
  std::cout << "Part II : " << sight_occupied << "\n";
}
