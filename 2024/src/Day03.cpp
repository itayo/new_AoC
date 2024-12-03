#include "Day03.h"
#include <iostream>
#include <regex>

void Day03::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    std::regex rx("mul\\(([0-9]*,[0-9]*)\\)");
    std::vector<std::string> tmp;

    for (auto &line: raw) {
        formatted.line.append(line);
        auto row = aoc.ExtractMatches(rx, line);
        for (auto &r: row) {
            formatted.lines.emplace_back(r);
            auto digits = aoc.GetAllIntegersS32(r);
            formatted.muls.emplace_back(digits[0], digits[1]);
        }

    }

}

int32_t Day03::Execute1(Data data) {
    uint32_t result = 0;
    for (auto &mul: data.muls) {
        result += (mul.x * mul.y);
    }
    return result;
}

int32_t Day03::Execute2(Data data) {
    uint32_t result = 0;
    const std::string &line = data.line;
    std::regex rx("(don't\\(\\))|(do\\(\\))|mul\\(([0-9]*,[0-9]*)\\)");
    bool isEnabled = true;
    auto finds = aoc.ExtractMatches(rx, line);
    finds.erase(std::remove(finds.begin(), finds.end(), ""), finds.end());


    for (auto &find: finds) {
        if (find == "don't()") { isEnabled = false; }
        else if (find == "do()") { isEnabled = true; }
        else if (isEnabled) {
            auto tmp = aoc.GetAllIntegersS32(find);
            result += tmp[0] * tmp[1];
        }
    }

    return result;
}

bool Day03::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day03::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}


bool Day03::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day03::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
