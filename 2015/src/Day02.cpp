#include "Day02.h"
#include <iostream>

void Day02::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    for(auto &line:raw) {
        std::vector<int32_t> sizes = aoc.GetAllIntegersS32(line);
        formatted.packages.emplace_back(sizes[0],sizes[1],sizes[2]);
    }
}

uint32_t Day02::Execute1(Data data) {
    uint32_t total=0;
    for(auto &package: data.packages){
        total += Internal::paper_needed(package);
    }
    return total;
}

uint32_t Day02::Execute2(Data data) {
    uint32_t total=0;
    for(auto &package: data.packages){
        total += Internal::ribbon_needed(package);
    }
    return total;
}

bool Day02::testPart1() {
    auto result=Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day02::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}



bool Day02::testPart2() {
    auto result=Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day02::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
