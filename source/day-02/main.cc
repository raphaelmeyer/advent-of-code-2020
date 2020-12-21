#include "password.h"

#include <iostream>

int main() {
  auto const passwords = parse_input(std::cin);

  std::cout << "Part I : " << count_valid_passwords<OldPolicy>(passwords)
            << "\n";

  std::cout << "Part II : " << count_valid_passwords<NewPolicy>(passwords)
            << "\n";
}
