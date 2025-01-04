#ifndef DAY22_H
#define DAY22_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>


class Day22 : public DayBase {
public:
    Day22() {
        m_rawDataA = aoc.ReadFile("Data/input22A.txt");
        m_rawDataB = aoc.ReadFile("Data/input22B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input22A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input22B.txt");
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
        std::vector<uint64_t> Numbers;
        std::vector<std::string> Raw;

    };
    const uint64_t ExpectedTestA = 37327623;
    const int32_t ExpectedTestB = 23;

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

    int32_t Execute2(Data data);

    void Evolve(uint64_t &SIP);
};


#endif // DAY22_H
