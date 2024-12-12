#ifndef DAY12_H
#define DAY12_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>


class Day12 : public DayBase {
public:
    Day12() {
        m_rawDataA = aoc.ReadFile("Data/input12A.txt");
        m_rawDataB = aoc.ReadFile("Data/input12B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input12A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input12B.txt");
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
        uint64_t rows=1;
        uint64_t cols=1;
        std::vector<std::string> raw;
    };
    const uint64_t ExpectedTestA = 1930;
    const uint64_t ExpectedTestB = 1206;

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

    uint64_t Execute1(Data data);

    uint64_t Execute2(Data data);
    int sides(const std::vector<std::vector<char>>& grid, const std::vector<std::vector<char>>& gridCopy, int row, int col);
    int priceRegionSides(std::vector<std::vector<char>>& grid, const std::vector<std::vector<char>>& gridCopy, int startRow, int startCol);
    std::vector<int> dR = {-1, 0, 1, 0}; // UP, RIGHT, DOWN, LEFT
    std::vector<int> dC = {0, 1, 0, -1};
};


#endif // DAY12_H
