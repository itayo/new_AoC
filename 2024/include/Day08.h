#ifndef DAY08_H
#define DAY08_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>
#include <AoC/Grid2D.h>
#include <set>


class Day08 : public DayBase {
public:
    Day08() {
        m_rawDataA = aoc.ReadFile("Data/input08A.txt");
        m_rawDataB = aoc.ReadFile("Data/input08B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input08A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input08B.txt");
        PrepareData();
    }


    std::string part1() override;

    std::string part2() override;

    bool testPart1() override;

    bool testPart2() override;

private:

    class Internal {
    public:
        void none() {};
        //defineDayFunctions
    };

    struct Data {
        std::unordered_map<char,std::vector<std::pair<int,int>>> antennas;
        int X,Y;
    };

    const uint32_t ExpectedTestA = 14;
    const uint32_t ExpectedTestB = 34;

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


#endif // DAY08_H
