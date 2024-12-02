#ifndef DAYRESULT_H
#define DAYRESULT_H

#include <chrono>
#include <string>

struct DayResult {
    std::chrono::duration<double, std::micro> part1ExecutionTime;
    std::string part1Result;
    bool testPart1Result;

    std::chrono::duration<double, std::micro> part2ExecutionTime;
    std::string part2Result;
    bool testPart2Result;
};

#endif // DAYRESULT_H