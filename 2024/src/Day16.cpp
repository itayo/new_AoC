#include "Day16.h"
#include <AoC/Grid2D.h>
#include <AoC/Vector2D.h>
#include <unordered_set>
#include <queue>

void Day16::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    auto &map = formatted.map;
    map.Reset(raw.size(), raw[0].size(), '.');
    for (size_t x = 0; x < raw.size(); ++x) {
        for (size_t y = 0; y < raw[x].size(); ++y) {
            if (raw[x][y] != '.') map.Set(x, y, raw[x][y]);
        }
    }
    formatted.start = map.FindPos('S');
    formatted.start.SetFacing(AoC::Vector2D::EAST);
    formatted.goal = map.FindPos('E');
    map.Set(formatted.start, '.');
    map.Set(formatted.goal, '.');

}

void Day16::findLowestScore(const AoC::Grid2D<char> &grid, Data &data) {

    const auto &start = data.start;
    const auto &end = data.goal;
    std::unordered_map<AoC::Vector2D, uint64_t, AoC::Vector2DFullHash> visited;
    std::priority_queue<std::pair<AoC::Vector2D, uint64_t>,
            std::vector<std::pair<AoC::Vector2D, uint64_t>>,
            Internal::CompareCost> pq;

    visited[start] = 0;
    pq.push({start, 0});
    while (!pq.empty()) {
        auto [pos, cost] = pq.top();
        pq.pop();
        if (pos.X() == end.X() && pos.Y() == end.Y() && cost <= data.cheapestCost) {
            data.cheapestCost = cost;
        }
        std::vector<std::pair<AoC::Vector2D, uint64_t>> group{{pos, 1},
                                                              {pos, 1000},
                                                              {pos, 1000}};
        group[0].first.GoForward();
        group[1].first.TurnLeft();
        group[2].first.TurnRight();
        for (auto next: group) {
            if ((grid.Exists(next.first) && grid.Get(next.first) != '#') && visited.count(next.first) == 0 ||
                visited[next.first] >= (cost + next.second)) {
                pq.push({next.first, cost + next.second});
                visited[next.first] = cost + next.second;
            }
        }
    }

}

uint64_t Day16::Execute1(Data data) {
    findLowestScore(data.map, data);
    uint64_t result = data.cheapestCost; //
    return result;

}

uint64_t Day16::Execute2(Data data) {
    uint64_t result = 0;
    return result;
}

bool Day16::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day16::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}


bool Day16::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day16::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
