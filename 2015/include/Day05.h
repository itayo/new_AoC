#ifndef DAY05_H
#define DAY05_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>


class Day05 : public DayBase {
public:
    Day05() {
        m_rawDataA = aoc.ReadFile("Data/input05A.txt");
        m_rawDataB = aoc.ReadFile("Data/input05B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input05A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input05B.txt");
        PrepareData();
    }


    std::string part1() override;

    std::string part2() override;

    bool testPart1() override;

    bool testPart2() override;

private:

    class Internal {
    public:
        void none(){};
        //defineDayFunctions
    };
    struct Data {
        std::vector<std::string> strings;

    };
    const uint32_t ExpectedTestA = 2;
    const uint32_t ExpectedTestB = 2;

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
        PrepareData(m_rawDataB, m_DataB);
        PrepareData(m_rawDataTestA, m_DataTestA);
        PrepareData(m_rawDataTestB, m_DataTestB);
    }

    void PrepareData(std::vector<std::string> &raw, Data &formatted);

    uint32_t Execute1(Data data);

    uint32_t Execute2(Data data);
};


#endif // DAY05_H
