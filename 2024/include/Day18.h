#ifndef DAY18_H
#define DAY18_H

#include "DayBase.h"
#include "AoC/Vector2D.h"
#include "AoC/Grid2D.h"
#include <string>
#include <AoC/aoc.h>
#include <unordered_set>


class Day18 : public DayBase {
public:
    Day18() {
        m_rawDataA = aoc.ReadFile("Data/input18A.txt");
        m_rawDataB = aoc.ReadFile("Data/input18B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input18A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input18B.txt");
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
        struct Node {
            AoC::Vector2D position;
            int gCost, hCost;
            Node* parent;

            Node(AoC::Vector2D position, int gCost, int hCost, Node* parent = nullptr)
                    : position(position), gCost(gCost), hCost(hCost), parent(parent) {}

            [[nodiscard]] int fCost() const { return gCost + hCost; }

            bool operator<(const Node& other) const { return fCost() > other.fCost(); }
        };
    };
    struct Data {
        size_t gridSize=1;
        AoC::Vector2D start{0,0};
        AoC::Vector2D goal{0,0};
        AoC::Grid2D<int> map{1,1,0};
        std::vector<AoC::Vector2D> corruptions;

    };
    const uint64_t ExpectedTestA = 22;
    const std::string ExpectedTestB = "6,1";

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

    std::string Execute2(Data data);
    std::pair<std::vector<AoC::Vector2D>, int> aStar(const AoC::Grid2D<int>& grid, const AoC::Vector2D& start, const AoC::Vector2D& goal);
};


#endif // DAY18_H
