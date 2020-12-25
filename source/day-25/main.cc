#include "door.h"

#include <iostream>

int main() {
  auto card = brute_force(7, 15733400);
  auto door = brute_force(7, 6408062);

  auto e1 = transform(6408062, card);
  auto e2 = transform(15733400, door);

  if (e1 != e2) {
    throw std::logic_error{"secret not so shared"};
  }

  std::cout << "Part I : " << e1 << "\n";
  std::cout << "Part II : "
            << "phew..."
            << "\n";
}
