#include "Day10.h"
#include <iostream>
#include <set>
#include <unordered_set>

void Day10::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    formatted.map = AoC::Grid2D<int>(raw.size(), raw[0].size());
    for (size_t row = 0; row < raw.size(); row++) {
        for (size_t col = 0; col < raw[0].size(); col++) {
            formatted.map.Set(row, col, raw[row][col] - '0');
        }
    }
}

uint32_t search(const AoC::Vector2D &pos, std::set<std::pair<int, int>> &seen, AoC::Grid2D<int> &map, int height,
                std::function<bool(AoC::Grid2D<int> &, const AoC::Vector2D &,
                                   const std::set<std::pair<int, int>> &)> eval) {
    static const std::vector<AoC::Vector2D> offsets{AoC::Vector2D(0, 1),
                                                    AoC::Vector2D(0, -1),
                                                    AoC::Vector2D(1, 0),
                                                    AoC::Vector2D(-1, 0)};
    if (map.Exists(pos) && map.Get(pos) == height) {

        if (eval(map, pos, seen)) {
            int res = 0;
            for (auto dir: offsets) {
                res += search(pos + dir, seen, map, height + 1, eval);
            }
            return res;

        }
        seen.insert({pos.X(), pos.Y()});
        return 1;
    }
    return 0;
}

bool eval1(AoC::Grid2D<int> &map, const AoC::Vector2D &pos, const std::set<std::pair<int, int>> &set) {
    bool h = map.Get(pos) < 9;
    bool c = set.count({pos.X(), pos.Y()});
    return h || c;
}

bool eval2(AoC::Grid2D<int> &map, const AoC::Vector2D &pos, const std::set<std::pair<int, int>> &set) {
    return map.Get(pos) < 9;
}

uint32_t Day10::Execute1(Data data) {
    uint32_t result = 0;
    auto test = eval1;

    auto places = data.map.FindAllLocationsOf(0);
    for (AoC::Vector2D &place: places) {
        std::set<std::pair<int, int>> seen;
        result += search(place, seen, data.map, 0, eval1);
    }
    return result;
}

uint32_t Day10::Execute2(Data data) {
    uint32_t result = 0;
    auto test = eval1;

    auto places = data.map.FindAllLocationsOf(0);
    for (AoC::Vector2D &place: places) {
        std::set<std::pair<int, int>> seen;
        result += search(place, seen, data.map, 0, eval2);
    }
    return result;
}

bool Day10::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day10::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}


bool Day10::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day10::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
