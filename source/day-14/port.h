#pragma once

#include <istream>
#include <map>
#include <variant>
#include <vector>

struct UpdateMask {
  uint64_t mask;
  uint64_t value;
};

struct UpdateMemory {
  uint64_t address;
  uint64_t value;
};

using Memory = std::map<uint64_t, uint64_t>;
using Program = std::vector<std::variant<UpdateMask, UpdateMemory>>;

Program parse_input(std::istream &input);
Memory run_program(Program const &program);
uint64_t sum_mem(Memory const &memory);

Memory run_program_v2(Program const &program);
