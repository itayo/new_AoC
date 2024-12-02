#ifndef DAYBASE_H
#define DAYBASE_H

#include <string>
#include "TestData.h"

class DayBase {
public:
    virtual ~DayBase() = default;

    virtual std::string part1() { return "N/A"; };

    virtual std::string part2() { return "N/A"; };

    virtual bool testPart1() { return false; };

    virtual bool testPart2() { return false; };
};

#endif // DAYBASE_H
