#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "bus.h"

#include <sstream>

std::string example{R"(939
7,13,x,x,59,x,31,19
)"};

TEST_CASE("Example - Part I") {
  std::istringstream input{example};
  auto const [from, timetable] = parse_input(input);
  auto const departure = find_bus_after(from, timetable);

  REQUIRE(departure.time == 944);
  REQUIRE(departure.id == 59);

  auto const result = calc_result(from, departure);

  REQUIRE(result == 295);
}

TEST_CASE("Example - Part II") {
  std::istringstream input{example};
  auto const [from, timetable] = parse_input(input);

  REQUIRE(find_earliest_subsequent(timetable) == 1068781);
}

TEST_CASE("Part II - more examples") {
  std::string data{};
  uint64_t expected = 0;

  SUBCASE("1") {
    data = "67,7,59,61";
    expected = 754018;
  }
  SUBCASE("2") {
    data = "67,x,7,59,61";
    expected = 779210;
  }
  SUBCASE("3") {
    data = "67,7,x,59,61";
    expected = 1261476;
  }
  SUBCASE("4") {
    data = "1789,37,47,1889";
    expected = 1202161486;
  }

  std::istringstream input{data};
  auto const [from, timetable] = parse_input(input);

  REQUIRE(find_earliest_subsequent(timetable) == expected);
}

TEST_CASE("split string") {
  auto const list = split_string("4,2,x,x,7,x,3", ",");
  REQUIRE(list.size() == 7);

  REQUIRE(list[1] == "2");
  REQUIRE(list[2] == "x");
  REQUIRE(list[6] == "3");
}

TEST_CASE("Parse input") {
  std::istringstream input{example};
  auto const [from, timetable] = parse_input(input);

  REQUIRE(from == 939);
  REQUIRE(timetable.size() == 8);
  REQUIRE(timetable[6] == 31);
}
