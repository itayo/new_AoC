#include "Day20.h"
#include <iostream>

void Day20::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    formatted.Map = raw;
    bool startFound = false;
    bool goalFound = false;
    for (int32_t x = 0; x < raw.size(); ++x) {
        for (int32_t y = 0; y < raw[x].size(); ++y) {
            switch (raw[x][y]) {
                case 'S':
                    formatted.Start = {x, y};
                    startFound = true;
                    break;
                case 'E':
                    formatted.Goal = {x, y};
                    goalFound = true;
                    break;
                default:
                    break;
            }
        }
    }

}

uint64_t Day20::Execute1(Data data) {
    uint64_t result = 0;
    static constexpr std::array<AoC::Position, 4> PositionDirections{
            {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}
    };

    std::deque<std::tuple<AoC::Position, int, std::unordered_map<AoC::Position, int, AoC::Position::PositionHasher>>> queue;
    std::unordered_map<AoC::Position, int, AoC::Position::PositionHasher> visited;
    queue.push_back({data.Start, 0, visited});
    while (!queue.empty()) {
        auto [pos, time, visited_copy] = queue.front();

        queue.pop_front();
        visited_copy[pos] = time;
        if (pos == data.Goal) {
            std::swap(visited,visited_copy);
            break;
        }
        for (auto dir: PositionDirections) {
            AoC::Position neighbor = pos + dir;
            if (neighbor[0] >= 0 && neighbor[0] < data.Map.size() && neighbor[1] >= 0 && neighbor[1] < data.Map[0].size() &&
                visited_copy.find(neighbor) == visited_copy.end() && data.Map[neighbor[0]][neighbor[1]] != '#') {
                auto new_visited = visited_copy;
                queue.push_back({neighbor, time + 1, new_visited});
            }
        }
    }
    for (const auto &[pos, t1]: visited) {
        for (auto dir: PositionDirections) {
            AoC::Position neighbor = pos + dir * 2;
            if (visited.find(neighbor) != visited.end() && visited.at(neighbor) - t1 >= 102) {
                result++;
            }
        }
    }


    return result;

}

uint64_t Day20::Execute2(Data data) {
    uint64_t result = 0;
    int m = data.Map.size();
    int n = data.Map[0].size();

    static constexpr std::array<AoC::Position, 4> PositionDirections{
            {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}
    };

     static constexpr int threshold = 100;
    std::vector<AoC::Position> path;
    std::deque<std::tuple<AoC::Position, int, std::unordered_map<AoC::Position, int, AoC::Position::PositionHasher>>> queue;
    std::unordered_map<AoC::Position, int, AoC::Position::PositionHasher> visited;
    queue.push_back({data.Start, 0, {}});

    while (!queue.empty()) {
        auto [pos, time, currVisited] = queue.front();
        queue.pop_front();

        currVisited[pos] = time;

        if (pos == data.Goal) {
            std::swap(visited, currVisited);
            break;
        }

        for (auto dir : PositionDirections) {
            AoC::Position nPos = pos + dir;

            if (nPos[0] >= 0 && nPos[0] < m && nPos[1] >= 0 && nPos[1] < n && data.Map[nPos[0]][nPos[1]] != '#' && currVisited.find(nPos) == currVisited.end()) {
                queue.push_back({nPos, time + 1, currVisited});
            }
        }
    }
    for (const auto& [pos, t1] : visited) {
        path.push_back(pos);
    }
    std::sort(path.begin(), path.end(), [&](const AoC::Position& a, const AoC::Position& b) {
        return visited[a] < visited[b];
    });

    for (size_t t2 = threshold; t2 < path.size(); ++t2) {
        for (size_t t1 = 0; t1 < t2 - threshold; ++t1) {
            int x1 = path[t1][0], y1 = path[t1][1];
            int x2 = path[t2][0], y2 = path[t2][1];
            int distance = abs(x1 - x2) + abs(y1 - y2);

            if (distance <= 20 && (t2 - t1 - distance) >= threshold) {
                ++result;
            }
        }
    }
    return result;
}

bool Day20::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day20::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}


bool Day20::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day20::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
