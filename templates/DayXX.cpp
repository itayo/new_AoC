#include "DayXX.h"
#include <iostream>

void DayXX::PrepareData(std::vector<std::string> &raw, Data &formatted) {

}

uint64_t DayXX::Execute1(Data &data) {
    uint64_t result=0;
    return result;

}

uint64_t DayXX::Execute2(Data &data) {
    uint64_t result=0;
    return result;
}

bool DayXX::testPart1() {
    auto result=Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string DayXX::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}



bool DayXX::testPart2() {
    auto result=Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string DayXX::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
