#include "door.h"

uint64_t transform(uint64_t base, uint64_t private_key) {
  uint64_t value = 1;
  for (unsigned i = 0; i < private_key; ++i) {
    value *= base;
    value %= 20201227;
  }

  return value;
}

uint64_t brute_force(uint64_t base, uint64_t public_key) {
  uint64_t private_key = 1;
  auto value = base;
  while (value != public_key) {
    value *= base;
    value %= 20201227;
    ++private_key;
  }

  return private_key;
}
