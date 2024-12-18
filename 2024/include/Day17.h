#ifndef DAY17_H
#define DAY17_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>
#include <deque>


class Day17 : public DayBase {
public:
    Day17() {
        m_rawDataA = aoc.ReadFile("Data/input17A.txt");
        m_rawDataB = aoc.ReadFile("Data/input17B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input17A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input17B.txt");
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
        Data() : registers(3, 0) {}

        std::vector<uint64_t> registers;

        std::vector<int> opcodes;

    };

    const std::string ExpectedTestA = "4,6,3,5,6,3,5,2,1,0";
    const uint64_t ExpectedTestB = 117440;

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

    std::string Execute1(Data &data);

    uint64_t Execute2(Data &data);

    static std::vector<uint64_t> run(Data &data);

    uint64_t dive(const std::vector<int> &goal, Data &data, uint64_t a = 0, int depth = 0);
};


#endif // DAY17_H
