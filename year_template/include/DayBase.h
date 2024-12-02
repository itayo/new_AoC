#ifndef DAYBASE_H
#define DAYBASE_H

#include <string>
#include "TestData.h"

class DayBase {
public:
    virtual ~DayBase() = default;
    virtual std::string part1() = 0;
    virtual std::string part2() = 0;
    virtual bool testPart1(const TestData& testData) = 0;
    virtual bool testPart2(const TestData& testData) = 0;
};

#endif // DAYBASE_H
