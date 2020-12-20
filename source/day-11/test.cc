#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "seats.h"

#include <sstream>

std::string example{R"(L.LL.LL.LL
LLLLLLL.LL
L.L.L..L..
LLLL.LL.LL
L.LL.LL.LL
L.LLLLL.LL
..L.L.....
LLLLLLLLLL
L.LLLLLL.L
L.LLLLL.LL
)"};

TEST_CASE("Example - Part I") {
  std::istringstream input{example};

  auto const seats = parse_input(input);
  auto const final_seats =
      simulate_until_stable(seats, {Decision::Adjacent, 4});
  auto const occupied = count_occupied(final_seats);

  REQUIRE(occupied == 37);
}

TEST_CASE("count neighbors") {
  Seats seats{
      {Seat::Floor, Seat::Empty, Seat::Occupied, Seat::Floor},
      {Seat::Occupied, Seat::Empty, Seat::Occupied, Seat::Empty},
      {Seat::Empty, Seat::Floor, Seat::Empty, Seat::Occupied},
      {Seat::Occupied, Seat::Empty, Seat::Empty, Seat::Empty},
  };
  REQUIRE(count_neighbors(seats, 1, 1) == 3);
  REQUIRE(count_neighbors(seats, 2, 2) == 2);

  REQUIRE(count_neighbors(seats, 0, 2) == 2);
  REQUIRE(count_neighbors(seats, 3, 0) == 2);
  REQUIRE(count_neighbors(seats, 3, 3) == 1);
}

TEST_CASE("count occupied") {
  Seats seats{
      {Seat::Floor, Seat::Empty, Seat::Occupied, Seat::Floor},
      {Seat::Occupied, Seat::Empty, Seat::Occupied, Seat::Empty},
      {Seat::Empty, Seat::Floor, Seat::Empty, Seat::Occupied},
      {Seat::Occupied, Seat::Empty, Seat::Empty, Seat::Empty},
  };
  REQUIRE(count_occupied(seats) == 5);
}

TEST_CASE("Simulate all empty") {
  Seats seats{
      {Seat::Floor, Seat::Empty, Seat::Floor, Seat::Floor},
      {Seat::Empty, Seat::Empty, Seat::Empty, Seat::Empty},
      {Seat::Floor, Seat::Floor, Seat::Empty, Seat::Floor},
      {Seat::Empty, Seat::Empty, Seat::Floor, Seat::Empty},
  };

  auto result = simulate(seats, {Decision::Adjacent, 4});

  REQUIRE(std::holds_alternative<Seats>(result));

  auto const after = std::get<Seats>(result);

  REQUIRE(after[0][0] == Seat::Floor);
  REQUIRE(after[0][1] == Seat::Occupied);
  REQUIRE(after[0][2] == Seat::Floor);
  REQUIRE(after[0][3] == Seat::Floor);

  REQUIRE(after[1][0] == Seat::Occupied);
  REQUIRE(after[1][1] == Seat::Occupied);
  REQUIRE(after[1][2] == Seat::Occupied);
  REQUIRE(after[1][3] == Seat::Occupied);

  REQUIRE(after[2][0] == Seat::Floor);
  REQUIRE(after[2][1] == Seat::Floor);
  REQUIRE(after[2][2] == Seat::Occupied);
  REQUIRE(after[2][3] == Seat::Floor);

  REQUIRE(after[3][0] == Seat::Occupied);
  REQUIRE(after[3][1] == Seat::Occupied);
  REQUIRE(after[3][2] == Seat::Floor);
  REQUIRE(after[3][3] == Seat::Occupied);
}

TEST_CASE("Simulate all occupied") {
  Seats seats{
      {Seat::Floor, Seat::Occupied, Seat::Floor, Seat::Floor},
      {Seat::Occupied, Seat::Occupied, Seat::Occupied, Seat::Occupied},
      {Seat::Floor, Seat::Floor, Seat::Occupied, Seat::Floor},
      {Seat::Occupied, Seat::Occupied, Seat::Floor, Seat::Occupied},
  };

  auto result = simulate(seats, {Decision::Adjacent, 4});

  REQUIRE(std::holds_alternative<Seats>(result));

  auto const after = std::get<Seats>(result);

  REQUIRE(after[0][0] == Seat::Floor);
  REQUIRE(after[0][1] == Seat::Occupied);
  REQUIRE(after[0][2] == Seat::Floor);
  REQUIRE(after[0][3] == Seat::Floor);

  REQUIRE(after[1][0] == Seat::Occupied);
  REQUIRE(after[1][1] == Seat::Empty);
  REQUIRE(after[1][2] == Seat::Empty);
  REQUIRE(after[1][3] == Seat::Occupied);

  REQUIRE(after[2][0] == Seat::Floor);
  REQUIRE(after[2][1] == Seat::Floor);
  REQUIRE(after[2][2] == Seat::Empty);
  REQUIRE(after[2][3] == Seat::Floor);

  REQUIRE(after[3][0] == Seat::Occupied);
  REQUIRE(after[3][1] == Seat::Occupied);
  REQUIRE(after[3][2] == Seat::Floor);
  REQUIRE(after[3][3] == Seat::Occupied);

  REQUIRE(count_occupied(after) == 6);
}

TEST_CASE("Example - Part II") {
  std::istringstream input{example};

  auto const seats = parse_input(input);
  auto const final_seats = simulate_until_stable(seats, {Decision::Sight, 5});
  auto const occupied = count_occupied(final_seats);

  REQUIRE(occupied == 26);
}
