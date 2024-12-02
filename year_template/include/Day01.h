#ifndef DAY01_H
#define DAY01_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>

class Day01 : public DayBase {
public:
    Day01() {
        m_rawDataA = aoc.ReadFile("Data/input01A.txt");
        m_rawDataB = aoc.ReadFile("Data/input01B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/Input01A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input01B.txt");
    }

    void PrepareData() {
        PrepareData(m_rawDataA,m_DataA);
    }

    std::string part1() override;

    std::string part2() override;

    bool testPart1(const TestData &testData) override;

    bool testPart2(const TestData &testData) override;

private:
    AoC::AoC aoc;
    std::vector<std::string> m_rawDataA;
    std::vector<std::string> m_rawDataB;
    std::vector<std::string> m_rawDataTestA;
    std::vector<std::string> m_rawDataTestB;
    std::vector<std::string> m_DataA;
    std::vector<std::string> m_DataB;
    std::vector<std::string> m_DataTestA;
    std::vector<std::string> m_DataTestB;

    void PrepareData(std::vector<std::string> &vector1, std::vector<std::string> &vector2);
};

#endif // DAY01_H
