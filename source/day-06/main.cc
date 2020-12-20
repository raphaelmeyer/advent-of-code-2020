#include "form.h"

#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

int main() {
  std::string line{};
  std::vector<uint> count_any{};
  std::vector<uint> count_all{};

  while (std::getline(std::cin, line)) {
    std::vector<std::string> answers{};
    while (not line.empty()) {
      answers.push_back(line);
      std::getline(std::cin, line);
    }
    count_any.push_back(any_yes(answers));
    count_all.push_back(all_yes(answers));
  }

  std::cout << std::accumulate(count_any.begin(), count_any.end(), 0) << "\n";
  std::cout << std::accumulate(count_all.begin(), count_all.end(), 0) << "\n";
}
