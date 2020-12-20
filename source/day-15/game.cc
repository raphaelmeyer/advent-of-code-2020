#include "game.h"

#include <algorithm>
#include <sstream>
#include <unordered_map>

uint nth_number(std::string input, uint nth) {
  std::istringstream iss{input};

  std::unordered_map<uint, uint> prevs{};

  uint last_n = 0;
  uint next = 0;

  iss >> last_n;
  uint last_turn = 1;

  while (not iss.eof()) {
    char comma;
    iss >> comma;
    if (iss.eof()) {
      break;
    }

    iss >> next;

    prevs[last_n] = last_turn;
    last_n = next;
    ++last_turn;
  }

  while (last_turn < nth) {
    if (prevs.contains(last_n)) {
      next = last_turn - prevs[last_n];
    } else {
      next = 0;
    }
    prevs[last_n] = last_turn;
    last_n = next;
    ++last_turn;
  }

  return last_n;
}
