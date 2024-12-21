#ifndef DAY16_H
#define DAY16_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>
#include <AoC/GenericHasher.h>
#include <unordered_set>
#include <array>
#include <queue>


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



    class Internal {
    public:
        enum tFacing {
            NORTH = 0,
            EAST = 1,
            SOUTH = 2,
            WEST = 3,
            END = 4
        };

        struct Position {
            std::array<int32_t, 2> coords{};

            int32_t &operator[](std::size_t index) { return coords[index]; }

            const int32_t &operator[](std::size_t index) const { return coords[index]; }

            bool operator==(const Position &other) const {
                return coords[0] == other.coords[0] && coords[1] == other.coords[1];
            }

            bool operator!=(const Position &other) const {
                return !(*this == other);
            }

            bool operator<(const Position &other) const {
                return std::tie(coords[0], coords[1]) < std::tie(other.coords[0], other.coords[1]);
            }

            bool operator<=(const Position &other) const {
                return !(other < *this);
            }

            bool operator>(const Position &other) const {
                return other < *this;
            }

            bool operator>=(const Position &other) const {
                return !(*this < other);
            }

            size_t operator()() {
                return GenericHasher::hash_impl(coords);
            }


            Position operator+(const Position &other) const {
                return {{coords[0] + other.coords[0], coords[1] + other.coords[1]}};
            }

            Position operator-(const Position &other) const {
                return {{coords[0] - other.coords[0], coords[1] - other.coords[1]}};
            }

            Position &operator+=(const Position &other) {
                coords[0] += other.coords[0];
                coords[1] += other.coords[1];
                return *this;
            }

            Position &operator-=(const Position &other) {
                coords[0] -= other.coords[0];
                coords[1] -= other.coords[1];
                return *this;
            }

            Position operator*(int32_t scalar) const {
                return {{coords[0] * scalar, coords[1] * scalar}};
            }

            Position &operator*=(int32_t scalar) {
                coords[0] *= scalar;
                coords[1] *= scalar;
                return *this;
            }
        };

        using MapElement = std::unordered_set<Position>;
        struct PositionHasher {
            std::size_t operator()(const Position& pos) const noexcept {
                return std::hash<int32_t>{}(pos.coords[0]) ^ (std::hash<int32_t>{}(pos.coords[1]) << 1);
            }
        };

        struct State {
            Position pos;
            tFacing dir;
            static constexpr int64_t stepFwd = 1;
            static constexpr int64_t Turn = 1000;

            std::vector<std::pair<State, uint64_t>> next() {
                static constexpr std::array<Position, 4> directions{
                        {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};
                static constexpr std::array<uint64_t,2> costs {1,1000};
                auto vel = directions[dir];
                std::pair<State,uint64_t> fwd{{pos + vel, dir},costs[0]};
                std::pair<State,uint64_t> left{{pos, static_cast<tFacing>((dir + 3) % END)},costs[1]};
                std::pair<State,uint64_t> right{{pos, static_cast<tFacing>((dir + 1) % END)},costs[1]};
                return {fwd, left, right};
            }


            bool operator==(const State &other) const {
                return pos == other.pos && dir == other.dir;
            }

            bool operator!=(const State &other) const {
                return !(*this == other);
            }

            bool operator<(const State &other) const {
                return std::tie(pos, dir) < std::tie(other.pos, other.dir);
            }

            bool operator<=(const State &other) const {
                return !(other < *this);
            }

            bool operator>(const State &other) const {
                return other < *this;
            }

            bool operator>=(const State &other) const {
                return !(*this < other);
            }

        };
        struct StateHasher {
            std::size_t operator()(const State& state) const noexcept {
                std::size_t h1 = std::hash<int32_t>{}(state.pos.coords[0]); // Hash x-coordinate
                std::size_t h2 = std::hash<int32_t>{}(state.pos.coords[1]); // Hash y-coordinate
                std::size_t h3 = std::hash<int>{}(state.dir);               // Hash tFacing
                return h1 ^ (h2 << 1) ^ (h3 << 2);                         // Combine hashes
            }
        };
    };
private:
    struct Data {
    public:
        int32_t width,height;
        Internal::Position Start,End;
        uint64_t cheapestCost = std::numeric_limits<uint64_t>::max();;
        std::unordered_set<Internal::Position, Internal::PositionHasher> paths;


    };

    const uint64_t ExpectedTestA = 11048;
    const uint64_t ExpectedTestB = 64;

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

    uint64_t Execute1(Data &data);

    uint64_t Execute2(Data &data);

    void findLowestScore(Data &data);
    uint64_t findLowestScore2(Data &data);

};
namespace std {
    template <>
    struct hash<Day16::Internal::Position> {
        std::size_t operator()(const Day16::Internal::Position& pos) const noexcept {
            // Combine the hashes of the two elements
            return std::hash<int32_t>{}(pos.coords[0]) ^ (std::hash<int32_t>{}(pos.coords[1]) << 1);
        }
    };
}


#endif // DAY16_H
