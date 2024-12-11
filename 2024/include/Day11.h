#ifndef DAY11_H
#define DAY11_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>
#include <queue>


class Day11 : public DayBase {
public:
    Day11() {
        m_rawDataA = aoc.ReadFile("Data/input11A.txt");
        m_rawDataB = aoc.ReadFile("Data/input11B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input11A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input11B.txt");
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
                std::vector<uint64_t> stones;

    };
    const uint64_t ExpectedTestA = 55312;
    const uint64_t ExpectedTestB = 65601038650482;

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
    uint64_t process_blinks(std::vector<uint64_t> &initialStones, size_t blinks);
    std::unordered_map<uint64_t, uint64_t> process_stone(uint64_t stone, uint64_t count);
};


#endif // DAY11_H
