#ifndef DAY21_H
#define DAY21_H

#include "DayBase.h"
#include "AoC/Position.h"
#include <string>
#include <AoC/aoc.h>
#include <AoC/Grid2D.h>


class Day21 : public DayBase {
public:
    Day21() {
        m_rawDataA = aoc.ReadFile("Data/input21A.txt");
        m_rawDataB = aoc.ReadFile("Data/input21B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input21A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input21B.txt");
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
        struct ArrayHasher {
            size_t operator()(const std::array<char, 2> &arr) const {
                size_t hash_value = 0;

                for (char c: arr) {
                    hash_value ^= std::hash<char>()(c) + 0x9e3779b9 + (hash_value << 6) + (hash_value >> 2);
                }

                return hash_value;
            }
        };

        using AllPathsMap = std::unordered_map<std::array<char, 2>, std::vector<std::string>, ArrayHasher>;

        Data() :
                NumericalKeyboard({"789", "456", "123", " 0A"}),
                DirectionalKeyboard({" ^A", "<v>"}) {}

        std::vector<std::string> Raw;
        const std::vector<std::string> NumericalKeyboard;
        const std::vector<std::string> DirectionalKeyboard;
        AllPathsMap NumericalPaths;
        AllPathsMap DirectionalPaths;
    };

    const uint64_t ExpectedTestA = 126384;
    const uint64_t ExpectedTestB = 126384;


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

    AoC::Position FindLocation(char c, const std::vector<std::string> &KEYPAD);

    void
    CacheShortestSequence(char fromKey, char toKey, const std::vector<std::string> &KEYPAD, Data::AllPathsMap &paths);

    void CacheAllShortestSequences(const std::vector<std::string> &KEYPAD, Data::AllPathsMap &Paths);

    void CacheAllShortestSequences(Data &data);

    std::string combinePart1(std::string codeStr, Data &data, int layer, int directionalRobots);

    uint64_t combinePart2(std::string codeStr, Data &data, int layer, int directionalRobots,
                          std::unordered_map<std::pair<std::string, int>, uint64_t, GenericHasher> &memory);
};


#endif // DAY21_H
