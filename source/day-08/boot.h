#pragma once

#include <istream>
#include <optional>
#include <string>
#include <vector>

struct Result {
  bool loop;
  int acc;
};

struct Instruction {
  std::string ins;
  int off;
};

using Program = std::vector<Instruction>;

Result find_loop(Program const &program);
int fix_code(Program const &program);

Program parse_code(std::istream &input);
