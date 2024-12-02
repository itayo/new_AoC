#include "Day01.h"
#include <iostream>

void Day01::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    formatted.line = raw[0];

}

uint32_t Day01::Execute1(Data data) {
    int32_t up = 0, down = 0;
    const char cUp = '(';
    const char cDown = ')';
    for (auto &c: data.line) {
        switch (c) {
            case cUp:
                ++up;
                break;
            case cDown:
                ++down;
                break;
            default:
                exit(1);
        }

    }
    return up - down;

}

uint32_t Day01::Execute2(Data data) {
    int32_t up = 0, down = 0,character=0;
    const char cUp = '(';
    const char cDown = ')';
    for (auto &c: data.line) {
        ++character;
        switch (c) {
            case cUp:
                ++up;
                break;
            case cDown:
                ++down;
                break;
            default:
                exit(1);
        }
        if(down > up) return character;

    }
    return up - down;
}

bool Day01::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day01::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}


bool Day01::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day01::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
