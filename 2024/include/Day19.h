#ifndef DAY19_H
#define DAY19_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>


class Day19 : public DayBase {
public:
    Day19() {
        m_rawDataA = aoc.ReadFile("Data/input19A.txt");
        m_rawDataB = aoc.ReadFile("Data/input19B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input19A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input19B.txt");
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

    };
    struct Data {
        size_t maxTowelLength;
        std::vector<std::string> towels;
        std::vector<std::string> designs;
    };
    const uint64_t ExpectedTestA = 6;
    const uint64_t ExpectedTestB = 16;

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
    uint64_t CanBeRebuiltTester(const std::string sut, const Data &data, const size_t depth,std::unordered_map<std::string, uint64_t> &cacher);
};


#endif // DAY19_H
