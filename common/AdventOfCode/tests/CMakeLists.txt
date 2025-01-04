enable_testing()

add_executable(
        AoCTests
        LinkedList.cpp
)
target_link_libraries(
        AoCTests
        GTest::gtest_main
        AdventOfCodeLib
)

include(GoogleTest)
gtest_discover_tests(AoCTests)