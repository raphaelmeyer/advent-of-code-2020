#include "bus.h"

#include <iostream>

int main() {
  auto const [from, timetable] = parse_input(std::cin);

  auto const departure = find_bus_after(from, timetable);
  auto const result = calc_result(from, departure);

  std::cout << "Part I : " << result << "\n";

  std::cout << "Part II : " << find_earliest_subsequent(timetable) << "\n";
}
