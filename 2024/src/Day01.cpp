#include "Day01.h"
#include <iostream>
void Day01::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    for(auto &line: raw) {
        std::vector<int32_t> resp = aoc.GetAllIntegersS32(line);
        formatted.left.emplace_back(resp[0]);
        formatted.right.emplace_back(resp[1]);
    }
}

uint32_t Day01::Execute1(Data data) {
    uint32_t result=0;
    auto &left=data.left;
    auto &right = data.right;
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    for (uint64_t i = 0; i < left.size(); ++i)
        result += left[i] > right[i] ? left[i] - right[i]: right[i] - left[i];
    return result;
}

uint32_t Day01::Execute2(Data data) {
    uint32_t result = 0;
    auto &left = data.left;
    auto &right = data.right;

    for (auto &num: left) {
        result += num * (std::count(right.begin(), right.end(), num));
    }
    return result;
}

bool Day01::testPart1() {
    auto result=Execute1(m_DataTestA);
    return ExpectedTestA == result;
}


std::string Day01::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}

bool Day01::testPart2() {
    auto result=Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day01::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}




