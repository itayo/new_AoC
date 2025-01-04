cmake_minimum_required(VERSION 3.20)
project(AoC VERSION 1.0.0)
include(FetchContent)

set(FORT_ENABLE_TESTING OFF CACHE INTERNAL "")

FetchContent_Declare(LIBFORTE
        GIT_REPOSITORY    https://github.com/seleznevae/libfort.git
        GIT_TAG           v0.4.2
        STEP_TARGETS      build
)

FetchContent_MakeAvailable(LIBFORTE)

FetchContent_Declare(GTEST
        GIT_REPOSITORY    https://github.com/google/googletest.git
        GIT_TAG           v1.15.2
        STEP_TARGETS      build
)

FetchContent_MakeAvailable(GTEST)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
find_package(OpenSSL REQUIRED)

add_subdirectory(common)
#add_subdirectory(year_template)
add_subdirectory(2015)
add_subdirectory(2024)