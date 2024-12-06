#ifndef DAY06_H
#define DAY06_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>
#include <AoC/Grid2D.h>
#include <AoC/Vector2D.h>
#include <set>


class Day06 : public DayBase {
public:
    Day06() {
        m_rawDataA = aoc.ReadFile("Data/input06A.txt");

        m_rawDataB = aoc.ReadFile("Data/input06B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input06A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input06B.txt");
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

    };

    struct Data {
        Data() {
            map = AoC::Grid2D<char>(1, 1);
        }

        AoC::Grid2D<char> map;
        AoC::Vector2D guard;
        AoC::Vector2D start;
        bool printMap=false;


    };

    const uint32_t ExpectedTestA = 41;
    const uint32_t ExpectedTestB = 6;

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

    void
    WalkTheWalk1(Data &data, std::set<std::pair<size_t, size_t>> &positions);
    void TryStep(AoC::Grid2D<char> &map, AoC::Vector2D &guard);
    int CountLoopPositions(Data &data);
};


#endif // DAY06_H
