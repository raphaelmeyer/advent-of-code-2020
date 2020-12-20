#include "port.h"

#include <numeric>
#include <ranges>
#include <regex>
#include <string>
#include <utility>

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

namespace {
std::regex mask_pattern{R"re(^mask = ([X01]{36})$)re"};
std::regex mem_pattern{R"re(^mem\[(\d+)\] = (\d+)$)re"};

UpdateMask parse_mask(std::string mask_str) {
  uint64_t mask = 0;
  uint64_t value = 0;
  for (auto c : mask_str) {
    mask <<= 1;
    value <<= 1;
    if (c == 'X') {
      mask |= 1;
    } else if (c == '1') {
      value |= 1;
    }
  }
  return UpdateMask{mask, value};
}

UpdateMemory parse_mem(std::string address_string, std::string value_string) {
  return {static_cast<uint>(std::stoul(address_string)),
          std::stoul(value_string)};
}

std::vector<uint64_t> generate_addresses(uint64_t address, UpdateMask mask) {
  std::vector<uint64_t> addresses{};

  std::vector<uint> floating{};
  uint64_t m = mask.mask;
  uint bit = 0;
  while (m > 0) {
    if (m & 1) {
      floating.push_back(bit);
    }
    ++bit;
    m >>= 1;
  }

  uint64_t const N = 1 << floating.size();
  for (uint64_t permutation = 0; permutation < N; ++permutation) {
    auto next_address = (address | mask.value) & (~mask.mask);
    for (uint bit = 0; bit < floating.size(); ++bit) {
      if (permutation & (1ul << bit)) {
        next_address |= (1ul << floating[bit]);
      }
    }
    addresses.push_back(next_address);
  }

  return addresses;
}

} // namespace

Program parse_input(std::istream &input) {
  Program program{};

  std::string line{};
  while (std::getline(input, line)) {
    std::smatch match{};
    if (std::regex_search(line, match, mask_pattern)) {
      auto update_mask = parse_mask(match.str(1));
      program.emplace_back(update_mask);
    } else if (std::regex_search(line, match, mem_pattern)) {
      auto update_mem = parse_mem(match.str(1), match.str(2));
      program.emplace_back(update_mem);
    }
  }

  return program;
}

Memory run_program(Program const &program) {
  UpdateMask mask{};
  Memory memory{};
  for (auto instruction : program) {
    std::visit(overloaded{[&](UpdateMask const &m) { mask = m; },
                          [&](UpdateMemory const &m) {
                            memory[m.address] =
                                (m.value & mask.mask) | mask.value;
                          }},
               instruction);
  }
  return memory;
}

Memory run_program_v2(Program const &program) {
  UpdateMask mask{};
  Memory memory{};

  for (auto instruction : program) {
    std::visit(overloaded{[&](UpdateMask const &m) { mask = m; },
                          [&](UpdateMemory const &m) {
                            auto addresses =
                                generate_addresses(m.address, mask);
                            for (auto address : addresses) {
                              memory[address] = m.value;
                            }
                          }},
               instruction);
  }
  return memory;
}

uint64_t sum_mem(Memory const &memory) {
  auto const values =
      std::ranges::views::values(memory) | std::ranges::views::common;
  return std::accumulate(values.begin(), values.end(), 0ul);
}
