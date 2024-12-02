#include "Day02.h"
#include <iostream>

void Day02::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    for (auto line: raw) {
        std::vector<int32_t> resp = aoc.GetAllIntegersS32(line);
        formatted.data.emplace_back(resp);
    }
}

uint32_t Day02::Execute1(Data data) {
    uint32_t result = 0;
    auto &vec = data;
    for (const auto &report: data.data) {
        auto diffs = Internal::calculate_difference(report);
        if (Internal::is_safe(diffs)) ++result;
    }
    return result;
}

uint32_t Day02::Execute2(Data data) {
    uint32_t result = 0;
    auto &vec = data;
    for (const auto &report: data.data) {
        auto diffs = Internal::calculate_difference(report);
        if (Internal::is_safe(diffs)) ++result;
        else {
            for (size_t i = 0; i < report.size(); ++i) {
                auto reduced(report);
                reduced.erase(reduced.begin() + i);
                diffs = Internal::calculate_difference(reduced);
                if (Internal::is_safe(diffs)) {
                    result++;
                    break;
                }
            }
        }
    }
    return result;
}

bool Day02::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day02::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}

bool Day02::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day02::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
