cmake_minimum_required(VERSION 3.10)
project(AdventOfCode_2015)
SET(AOC_YEARINFO "2015" CACHE STRING "YEAR VALUE")
set(CMAKE_CXX_STANDARD 17)
add_definitions( -DAOC_YEARINFO=${AOC_YEARINFO} )
include_directories(include)

# Add source files
add_executable(AdventOfCode_2015 main.cpp src/DayBase.cpp src/DayExecutor.cpp  src/Day01.cpp src/Day02.cpp src/Day03.cpp src/Day04.cpp src/Day04.cpp )#DayInsertPlace

add_custom_command(
        TARGET AdventOfCode_2015 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/TestData
        ${PROJECT_BINARY_DIR}/TestData
)

add_custom_command(
        TARGET AdventOfCode_2015 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/Data
        ${PROJECT_BINARY_DIR}/Data
)

target_link_libraries(AdventOfCode_2015  pthread)
target_link_libraries(AdventOfCode_2015  AdventOfCodeLib)
target_link_libraries(AdventOfCode_2015  fort)
target_link_libraries(AdventOfCode_2015  ${OPENSSL_LIBRARIES})

