#ifndef DAY02_H
#define DAY02_H

#include "DayBase.h"
#include "AoC/aoc.h"
#include <string>

class Day02 : public DayBase {
public:
    std::string part1() override;
    std::string part2() override;
    bool testPart1(const TestData& testData) override;
    bool testPart2(const TestData& testData) override;
    AoC::AoC aoc;
};

#endif // DAY02_H
