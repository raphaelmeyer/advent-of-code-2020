#include "boot.h"

#include <set>
#include <sstream>
#include <utility>

Program parse_code(std::istream &input) {
  Program program{};

  std::string line{};
  while (std::getline(input, line)) {
    std::istringstream iss{line};
    std::string instruction{};
    int offset = 0;
    iss >> instruction >> offset;
    program.push_back({instruction, offset});
  }

  return program;
}

Result run_code(Program const &program) {
  uint pc = 0;
  int acc = 0;

  std::set<uint> visited{};

  while (pc < program.size()) {
    visited.insert(pc);
    if (program[pc].ins == "acc") {
      acc += program[pc].off;
      ++pc;
    } else if (program[pc].ins == "jmp") {
      pc += program[pc].off;
    } else {
      ++pc;
    }
    if (visited.contains(pc)) {
      return {true, acc};
    }
  }

  return {false, acc};
}

Result find_loop(Program const &program) { return run_code(program); }

int fix_code(Program const &program) {
  auto copy = program;

  for (uint i = 0; i < copy.size(); ++i) {
    auto const orig = copy[i].ins;
    if (orig == "nop") {
      copy[i].ins = "jmp";
    } else if (orig == "jmp") {
      copy[i].ins = "nop";
    } else {
      continue;
    }

    auto const result = find_loop(copy);
    if (not result.loop) {
      return result.acc;
    }

    copy[i].ins = orig;
  }

  return 0;
}
