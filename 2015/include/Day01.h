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
        m_rawDataTestA = aoc.ReadFile("TestData/input01A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input01B.txt");
        PrepareData();
    }


    std::string part1() override;

    std::string part2() override;

    bool testPart1() override;

    bool testPart2() override;

private:
    struct Data {
        std::string line;
    };
    class Internal {
    public:
        static void non(int a){};

    };
    const uint32_t ExpectedTestA = -2;
    const uint32_t ExpectedTestB = 7;

    AoC::AoC aoc;
    std::vector<std::string> m_rawDataA;
    std::vector<std::string> m_rawDataB;
    std::vector<std::string> m_rawDataTestA;
    std::vector<std::string> m_rawDataTestB;
    Data m_DataA;
    Data m_DataB;
    Data m_DataTestA;
    Data m_DataTestB;

    void PrepareData() {
        PrepareData(m_rawDataA, m_DataA);
        PrepareData(m_rawDataA, m_DataB);
        PrepareData(m_rawDataTestA, m_DataTestA);
        PrepareData(m_rawDataTestB, m_DataTestB);
    }

    void PrepareData(std::vector<std::string> &raw, Data &formatted);

    uint32_t Execute1(Data data);

    uint32_t Execute2(Data data);
};


#endif // DAY01_H
