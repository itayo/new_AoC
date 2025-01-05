#ifndef DAY23_H
#define DAY23_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

class Day23 : public DayBase {
public:
    using NetworkMap = std::unordered_map<std::string, std::unordered_set<std::string>>;
    using NetworkNodes = std::unordered_set<std::string>;
    Day23() {
        m_rawDataA = aoc.ReadFile("Data/input23A.txt");
        m_rawDataB = aoc.ReadFile("Data/input23B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input23A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input23B.txt");
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
        AoC::AoCInput Raw;

    };
    const uint64_t ExpectedTestA = 7;
    const std::string ExpectedTestB = "co,de,ka,ta";

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

    uint64_t Execute1(Data &data);

    std::string Execute2(Data &data);

    std::pair<Day23::NetworkMap,NetworkNodes> parseInput(const AoC::AoCInput &puzzleInput);
};


#endif // DAY23_H
