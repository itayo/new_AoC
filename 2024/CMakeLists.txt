cmake_minimum_required(VERSION 3.10)
project(AdventOfCode_2024)

set(CMAKE_CXX_STANDARD 17)
set(FORT_ENABLE_TESTING OFF CACHE INTERNAL "")
include_directories(include)

# Add source files
add_executable(AdventOfCode_2024 main.cpp src/DayBase.cpp src/DayExecutor.cpp src/Day01.cpp src/Day02.cpp src/Day03.cpp src/Day04.cpp src/Day05.cpp src/Day06.cpp src/Day07.cpp src/Day08.cpp src/Day09.cpp src/Day10.cpp src/Day11.cpp src/Day12.cpp src/Day13.cpp src/Day14.cpp src/Day15.cpp src/Day16.cpp src/Day17.cpp src/Day18.cpp src/Day19.cpp src/Day20.cpp src/Day21.cpp )#DayInsertPlace

add_custom_command(
        TARGET AdventOfCode_2024 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/TestData
        ${PROJECT_BINARY_DIR}/TestData
        DEPENDS ${PROJECT_SOURCE_DIR}/TestData
)

add_custom_command(
        TARGET AdventOfCode_2024 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/Data
        ${PROJECT_BINARY_DIR}/Data
        DEPENDS ${PROJECT_SOURCE_DIR}/TestData
)


target_link_libraries(AdventOfCode_2024  pthread)
target_link_libraries(AdventOfCode_2024  AdventOfCodeLib)
target_link_libraries(AdventOfCode_2024  fort)

