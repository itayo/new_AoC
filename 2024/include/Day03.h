#ifndef DAY03_H
#define DAY03_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>


class Day03 : public DayBase {
public:
    Day03() {
        m_rawDataA = aoc.ReadFile("Data/input03A.txt");
        m_rawDataB = aoc.ReadFile("Data/input03B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input03A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input03B.txt");
        PrepareData();
    }


    std::string part1() override;

    std::string part2() override;

    bool testPart1() override;

    bool testPart2() override;

private:

    class Internal {
    public:
        static void dummy() { return; }

        //defineDayFunctions
        struct Mul {
            Mul(uint32_t px, uint32_t py) : x(px), y(py) {}

            uint32_t x;
            uint32_t y;
        };

    };

    struct Data {
        std::vector<std::string> lines;
        std::vector<Internal::Mul> muls;
        std::string line ="";


    };
    const uint32_t ExpectedTestA = 161;
    const uint32_t ExpectedTestB = 48;

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

    int32_t Execute1(Data data);

    int32_t Execute2(Data data);
};


#endif // DAY03_H
