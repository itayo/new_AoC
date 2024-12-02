
project(AdventOfCode_XXXX)
SET(LIBINTERFACE_VERSION 1 CACHE STRING "XXXX")
set(CMAKE_CXX_STANDARD 17)
add_definitions( -DVERSION_LIBINTERFACE=${LIBINTERFACE_VERSION} )
include_directories(include)

# Add source files
add_executable(AdventOfCode_XXXX main.cpp src/DayBase.cpp src/DayExecutor.cpp )#DayInsertPlace

add_custom_command(
        TARGET AdventOfCode_XXXX POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/TestData
        ${PROJECT_BINARY_DIR}/TestData
)

add_custom_command(
        TARGET AdventOfCode_XXXX POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/Data
        ${PROJECT_BINARY_DIR}/Data
)

target_link_libraries(AdventOfCode_XXXX  pthread)
target_link_libraries(AdventOfCode_XXXX  AdventOfCodeLib)
target_link_libraries(AdventOfCode_XXXX  fort)

