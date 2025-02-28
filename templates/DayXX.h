#ifndef DAYXX_H
#define DAYXX_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>


class DayXX : public DayBase {
public:
    DayXX() {
        m_rawDataA = aoc.ReadFile("Data/inputXXA.txt");
        m_rawDataB = aoc.ReadFile("Data/inputXXB.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/inputXXA.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/inputXXB.txt");
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

    };
    const uint64_t ExpectedTestA = ;
    const uint64_t ExpectedTestB = ;

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

    uint64_t Execute2(Data &data);
};


#endif // DAYXX_H
