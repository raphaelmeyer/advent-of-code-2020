set(DAY 05)
set(SOURCES seat.cc)

find_package(Boost REQUIRED)

add_library(day-${DAY})
target_sources(day-${DAY} PRIVATE ${SOURCES})
target_link_libraries(day-${DAY} PUBLIC settings Boost::headers)

add_executable(day-${DAY}-exe)
target_sources(day-${DAY}-exe PRIVATE main.cc)
target_link_libraries(day-${DAY}-exe PUBLIC day-${DAY})

add_executable(day-${DAY}-test)
target_sources(day-${DAY}-test PRIVATE test.cc)
target_link_libraries(day-${DAY}-test PRIVATE day-${DAY} doctest::doctest)
add_test(NAME "Day ${DAY}" COMMAND day-${DAY}-test)
