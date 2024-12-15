#ifndef DAY13_H
#define DAY13_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>


class Day13 : public DayBase {
public:
    Day13() {
        m_rawDataA = aoc.ReadFile("Data/input13A.txt");
        m_rawDataB = aoc.ReadFile("Data/input13B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input13A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input13B.txt");
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
        struct positions {
            explicit positions(const std::vector<uint64_t> &v) {
                x= v[0];
                y = v[1];
            }
            uint64_t x;
            uint64_t y;
        };
        struct Game {
            explicit Game(const std::vector<uint64_t> &va,const std::vector<uint64_t> &vb,const std::vector<uint64_t> &vg) : controllerA(va),
                                                                                                                    controllerB(vb),goal(vg) {}
            positions controllerA;
            positions controllerB;
            positions goal;

        };
        //defineDayFunctions
    };
    struct Data {
        std::vector<Internal::Game> games;

    };
    const uint64_t ExpectedTestA = 480;
    const uint64_t ExpectedTestB = 875318608908;

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
    std::pair<bool,uint64_t> ButtonSmasher1(const Internal::Game & game);
    std::pair<bool,uint64_t> ButtonSmasher2(const Internal::Game & game);
    uint64_t CostIfPrice(const Internal::Game &game, uint64_t offset = 0);
};


#endif // DAY13_H
