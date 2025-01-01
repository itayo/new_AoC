#ifndef DAY20_H
#define DAY20_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>
#include <AoC/Position.h>


class Day20 : public DayBase {
public:
    Day20() {
        m_rawDataA = aoc.ReadFile("Data/input20A.txt");
        m_rawDataB = aoc.ReadFile("Data/input20B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input20A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input20B.txt");
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
        AoC::Position Start,Goal;
        std::vector<std::string> Map;

    };
    const uint64_t ExpectedTestA = 0;
    const uint64_t ExpectedTestB = 0;

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

    uint64_t Execute1(Data data);

    uint64_t Execute2(Data data);
};


#endif // DAY20_H
