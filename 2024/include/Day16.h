#ifndef DAY16_H
#define DAY16_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>
#include <AoC/Grid2D.h>
#include <AoC/Vector2D.h>
#include <unordered_set>


class Day16 : public DayBase {
public:
    Day16() {
        m_rawDataA = aoc.ReadFile("Data/input16A.txt");
        m_rawDataB = aoc.ReadFile("Data/input16B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input16A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input16B.txt");
        PrepareData();
    }


    std::string part1() override;

    std::string part2() override;

    bool testPart1() override;

    bool testPart2() override;

private:

    class Internal {
    public:
        struct CompareCost {
            bool operator()(const std::pair<AoC::Vector2D, uint64_t> &lhs,
                            const std::pair<AoC::Vector2D, uint64_t> &rhs) const {
                return lhs.second > rhs.second;
            }
        };
    };
    struct Data {
        AoC::Grid2D<char> map{1,1,'.'};
        AoC::Vector2D start;
        AoC::Vector2D goal;
        uint64_t cheapestCost = std::numeric_limits<uint64_t>::max();

    };
    const uint64_t ExpectedTestA = 11048;
    const uint64_t ExpectedTestB = 0;

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

    static void PrepareData(std::vector<std::string> &raw, Data &formatted);

    uint64_t Execute1(Data data);

    uint64_t Execute2(Data data);
    void findLowestScore(const AoC::Grid2D<char> &grid, Data &data);

};


#endif // DAY16_H
