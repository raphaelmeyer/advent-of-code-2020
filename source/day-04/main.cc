#include "passport.h"

#include <iostream>

int main() {
  auto const passport_data = parse_input(std::cin);

  std::cout << "Part I : " << count_valid_passports(passport_data, Version::One)
            << "\n";

  std::cout << "Part II : "
            << count_valid_passports(passport_data, Version::Two) << "\n";
}
