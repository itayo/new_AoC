#ifndef DAY02_H
#define DAY02_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>


class Day02 : public DayBase {
public:
    Day02() {
        m_rawDataA = aoc.ReadFile("Data/input02A.txt");
        m_rawDataB = aoc.ReadFile("Data/input02B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input02A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input02B.txt");
        PrepareData();
    }


    std::string part1() override;

    std::string part2() override;

    bool testPart1() override;

    bool testPart2() override;

private:
    struct Data {
        std::vector<std::vector<int32_t>> data;
    };

    class Internal {
    public:
        static bool is_safe(const::std::vector<int32_t> &differences) {
            int pos=0,neg=0,total=differences.size();
            for(auto &diff: differences) {
                if(diff >=1 && diff <=3 ) pos++;
                else if(diff <=-1 && diff >=-3 ) neg++;
            }
            return pos == total || neg == total;
        }

        static std::vector<int32_t> calculate_difference(const std::vector<int32_t>& vec) {
            std::vector<int32_t> differences;
            for (size_t i = 1; i < vec.size(); ++i) {
                differences.push_back(vec[i] - vec[i - 1]);
            }
            return differences;

        }


    };
    const uint32_t ExpectedTestA = 2;
    const uint32_t ExpectedTestB = 4;

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


#endif // DAY02_H
