project("AdventOfCodeLib")


add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/aoc.cpp
        inc/AoC/aoc.h
        inc/AoC/Assertion.h
        inc/AoC/Grid2D.h
        inc/AoC/Vector2D.h
        inc/AoC/GenericHasher.h
        inc/AoC/Position.h
        inc/AoC/LinkedList.h
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/inc/aoc>
)
add_subdirectory(tests)
