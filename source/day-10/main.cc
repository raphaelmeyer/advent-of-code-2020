#include "jolt.h"

#include <iostream>

int main() {
  auto const adapters = parse_input(std::cin);
  auto const diffs = connect_jolt_adapters(adapters);

  std::cout << "[ " << diffs.one << " " << diffs.two << " " << diffs.three
            << " ]\n";

  std::cout << diffs.one * diffs.three << "\n";

  auto const permutations = jolt_permutations(adapters);
  std::cout << "permutations " << permutations << "\n";
}
