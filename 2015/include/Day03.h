#ifndef DAY03_H
#define DAY03_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>
#include <AoC/Vector2D.h>


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
    typedef std::unordered_map<char, std::function<void()>> ChristmasMover;
    typedef std::unordered_map<bool, ChristmasMover> MoveSelector;
    typedef std::unordered_map<bool, std::function<void()>> UpdateSelector;
    class Internal {
    public:

        //defineDayFunctions
    };
    struct Data {
        std::string data;
    };
    const uint32_t ExpectedTestA = 4;
    const uint32_t ExpectedTestB = 3;

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


#endif // DAY03_H
