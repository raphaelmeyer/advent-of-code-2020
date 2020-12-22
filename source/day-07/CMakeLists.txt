set(DAY 07)
set(SOURCES bag.cc)

add_library(day-${DAY})
target_sources(day-${DAY} PRIVATE ${SOURCES})
target_link_libraries(day-${DAY} PUBLIC settings)

add_executable(day-${DAY}-exe)
target_sources(day-${DAY}-exe PRIVATE main.cc)
target_link_libraries(day-${DAY}-exe PUBLIC day-${DAY})

add_executable(day-${DAY}-test)
target_sources(day-${DAY}-test PRIVATE test.cc)
target_link_libraries(day-${DAY}-test PRIVATE day-${DAY} doctest::doctest)
add_test(NAME "Day ${DAY}" COMMAND day-${DAY}-test)
