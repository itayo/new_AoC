#ifndef DAY15_H
#define DAY15_H

#include "DayBase.h"
#include "AoC/Vector2D.h"
#include "AoC/Grid2D.h"
#include <string>
#include <AoC/aoc.h>


class Day15 : public DayBase {
public:
    Day15() {
        m_rawDataA = aoc.ReadFile("Data/input15A.txt");
        m_rawDataB = aoc.ReadFile("Data/input15B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input15A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input15B.txt");
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
        using BigObjectType = std::pair<AoC::Vector2D,AoC::Vector2D>;
        using BigObjectVector = std::vector<BigObjectType>;
    };
    struct Data {

        AoC::Vector2D smallPlayer;
        AoC::Vector2D bigPlayer;
        AoC::Grid2D<char> smallMap;
        AoC::Grid2D<char> bigMap;
        std::vector<AoC::Vector2D> smallObjects;
        Internal::BigObjectVector bigObjects;
        std::vector<AoC::Vector2D> commands;
        std::pair<std::vector<std::string>,std::vector<::std::string>> raw;


    };
    const uint64_t ExpectedTestA = 10092;
    const uint64_t ExpectedTestB = 9021;

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
        PrepareData(m_rawDataTestA, m_DataTestA);
        PrepareData(m_rawDataTestB, m_DataTestB);
        PrepareData(m_rawDataA, m_DataA);
        PrepareData(m_rawDataB, m_DataB);
    }

    void PrepareData(std::vector<std::string> &raw, Data &formatted);

    uint64_t Execute1(Data data);

    uint64_t Execute2(Data data);
};


#endif // DAY15_H
