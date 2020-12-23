#include "jolt.h"

#include <iostream>

int main() {
  auto const adapters = parse_input(std::cin);

  auto const diffs = connect_jolt_adapters(adapters);
  std::cout << "Part I : " << diffs.one * diffs.three << "\n";

  auto const permutations = jolt_permutations(adapters);
  std::cout << "Part II : " << permutations << "\n";
}
