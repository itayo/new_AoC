#ifndef DAY09_H
#define DAY09_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>


class Day09 : public DayBase {
public:
    Day09() {
        m_rawDataA = aoc.ReadFile("Data/input09A.txt");
        m_rawDataB = aoc.ReadFile("Data/input09B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input09A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input09B.txt");
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
        struct fs {
            int id;
            int size;
            int pos;
        };
    };
    struct Data {
        std::string raw;
        std::vector<int64_t> fs;
    };
    const uint64_t ExpectedTestA = 1928;
    const uint64_t ExpectedTestB = 2858;

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
};


#endif // DAY09_H
