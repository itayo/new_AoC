cmake_minimum_required(VERSION 3.20)
include(FetchContent)

set(FORT_ENABLE_TESTING OFF CACHE INTERNAL "")

FetchContent_Declare(libfort
        GIT_REPOSITORY    https://github.com/seleznevae/libfort.git
        GIT_TAG           v0.4.2
        STEP_TARGETS      build
)

FetchContent_MakeAvailable(libfort)

add_subdirectory(common)
add_subdirectory(year_template)
add_subdirectory(2015)
add_subdirectory(2024)