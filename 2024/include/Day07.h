#ifndef DAY07_H
#define DAY07_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>


class Day07 : public DayBase {
public:
    Day07() {
        m_rawDataA = aoc.ReadFile("Data/input07A.txt");
        m_rawDataB = aoc.ReadFile("Data/input07B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input07A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input07B.txt");
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
        static uint64_t concatenate(uint64_t a, uint64_t b) {
            return std::stoull(std::to_string(a) + std::to_string(b));
        }
    };
    struct Data {
        uint64_t result;
        struct tPart {
            uint64_t expected;
            std::vector<int32_t> parts;
        };
        std::vector <tPart> parts;

    };
    const uint64_t ExpectedTestA = 3749;
    const uint64_t ExpectedTestB = 11387;

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


#endif // DAY07_H
