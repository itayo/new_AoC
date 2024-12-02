cmake_minimum_required(VERSION 3.20)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(FORT_ENABLE_TESTING OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(googletest)
include_directories(${GTEST_INCLUDE_DIRS})
FetchContent_Declare(libfort
        GIT_REPOSITORY    https://github.com/seleznevae/libfort.git
        GIT_TAG           v0.4.2
        STEP_TARGETS      build
)

FetchContent_MakeAvailable(libfort)

add_subdirectory(common)
add_subdirectory(year_template)
add_subdirectory(2024)