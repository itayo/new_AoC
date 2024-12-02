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

    class Internal {
    public:
        struct Package {
            Package(int32_t pw, int32_t pl, int32_t ph) : w(pw), l(pl), h(ph) {}

            int32_t w, l, h;
        };

        static int32_t paper_needed(const Package &package) {
            int32_t side1 = package.l * package.w;
            int32_t side2 = package.w * package.h;
            int32_t side3 = package.h * package.l;
            return 2 * (side1 + side2 + side3) + std::min({side1, side2,  side3});
        }

        static int32_t ribbon_needed(const Package &package) {
            int32_t side1 = 2*(package.l + package.w);
            int32_t side2 = 2*(package.w + package.h);
            int32_t side3 = 2*(package.h + package.l);
            return (package.l * package.w * package.h) + std::min({side1, side2,  side3});
        }

    };

    struct Data {
        std::vector<Internal::Package> packages;

    };
    const uint32_t ExpectedTestA = 58;
    const uint32_t ExpectedTestB = 34;

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
