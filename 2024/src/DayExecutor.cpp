#include "DayExecutor.h"
#include <iostream>

DayExecutor::DayExecutor(std::unique_ptr<DayBase> day) : m_day(std::move(day)) {}

DayResult DayExecutor::executePart1() {
    auto start = std::chrono::steady_clock::now();
    auto result = m_day->part1();
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double, std::micro> executionTime = end - start;

    return DayResult{
            .part1ExecutionTime = executionTime,
            .part1Result = result,
    };
}

DayResult DayExecutor::executePart2() {
    auto start = std::chrono::steady_clock::now();
    auto result = m_day->part2();
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double, std::micro> executionTime = end - start;

    return DayResult{
            .part2ExecutionTime = executionTime,
            .part2Result = result,
    };
}

bool DayExecutor::executeTestPart1() {
    // Only run the test and return the result, no timing paper_needed
    return m_day->testPart1();
}

bool DayExecutor::executeTestPart2() {
    // Only run the test and return the result, no timing paper_needed
    return m_day->testPart2();
}