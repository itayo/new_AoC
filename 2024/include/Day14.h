#ifndef DAY14_H
#define DAY14_H

#include "DayBase.h"
#include "AoC/Grid2D.h"
#include <string>
#include <AoC/aoc.h>


class Day14 : public DayBase {
public:
    Day14() {
        m_rawDataA = aoc.ReadFile("Data/input14A.txt");
        m_rawDataB = aoc.ReadFile("Data/input14B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input14A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input14B.txt");
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
        struct point {
            int64_t x;
            int64_t y;
        };
        struct robot {
            point pos;
            point vel;
        };
    };

    struct Data {
        Data(): grid(1,1,'0'), testGrid(1,1,'0') {}
        std::vector<Internal::robot> robots;
        AoC::Grid2D<char> grid;
        AoC::Grid2D<char> testGrid;

    };
    const uint32_t ExpectedTestA = 12;
    const uint32_t ExpectedTestB = 0;

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

    uint32_t Execute1(Data data, bool test);

    uint32_t Execute2(Data data, bool test);
};


#endif // DAY14_H
