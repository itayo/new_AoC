#ifndef DAYEXECUTOR_H
#define DAYEXECUTOR_H

#include "DayBase.h"
#include "DayResult.h"
#include "TestData.h"
#include <chrono>
#include <memory>

class DayExecutor {
public:
    explicit DayExecutor(std::unique_ptr<DayBase> day);

    DayResult executePart1();
    DayResult executePart2();
    bool executeTestPart1();
    bool executeTestPart2();

private:
    std::unique_ptr<DayBase> m_day;
};

#endif // DAYEXECUTOR_H