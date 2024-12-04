#include "Day04.h"
#include <iostream>

void Day04::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    formatted.prefix = raw[0];
}

uint32_t Day04::Execute1(Data data) {
    uint32_t result = 0;
    std::string md5 = "";
    static const std::string startsWith = "00000";


    while (true) {
        Internal::md5(data.prefix + std::to_string(result), md5);
        if (md5.rfind(startsWith, 0) == 0) {
            return result;
        }
        ++result;
    }
}

uint32_t Day04::Execute2(Data data) {
    uint32_t result = 0;
    std::string md5 = "";
    static const std::string startsWith = "000000";


    while (true) {
        Internal::md5(data.prefix + std::to_string(result), md5);
        if (md5.rfind(startsWith, 0) == 0) {
            return result;
        }
        ++result;
    }
}

bool Day04::testPart1() {
    auto result=Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day04::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}



bool Day04::testPart2() {
    auto result=Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day04::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
