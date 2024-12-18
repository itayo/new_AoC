#include "Day18.h"
#include <iostream>
#include <unordered_set>
#include <queue>



void Day18::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    size_t corruptedToPlace = 0;
    if (&formatted == &m_DataTestA) {
        formatted.gridSize = 7;
        corruptedToPlace = 12;
    } else if (&formatted == &m_DataTestB) {
        formatted.gridSize = 7;
        corruptedToPlace = 12;
    } else {
        formatted.gridSize = 71;
        corruptedToPlace = 1024;
    }
    formatted.map.Reset(formatted.gridSize,formatted.gridSize,0);
    formatted.start.Override(0,0);
    formatted.goal.Override(formatted.gridSize-1,formatted.gridSize-1);

    for (size_t i = 0; i < corruptedToPlace && i < raw.size(); ++i) {
        auto tmp = aoc.GetAllIntegersS32(raw[i]);
        int32_t x = tmp[1];
        int32_t y = tmp[0];
        formatted.map.Set(x,y,1);
    }
    for(size_t i=corruptedToPlace; i<raw.size();++i) {
        auto tmp = aoc.GetAllIntegersS32(raw[i]);
        int32_t x = tmp[1];
        int32_t y = tmp[0];
        formatted.corruptions.emplace_back(AoC::Vector2D{x, y});
    }
}

std::pair<std::vector<AoC::Vector2D>, int> Day18::aStar(const AoC::Grid2D<int>& grid, const AoC::Vector2D& start, const AoC::Vector2D& goal) {
    auto isValid = [&](const AoC::Vector2D& pos) {
        return grid.Exists(pos) && grid.Get(pos) == 0;
    };
    auto heuristic = [](const AoC::Vector2D& a, const AoC::Vector2D& b) {
        if((std::abs(a.X() - b.X()) + std::abs(a.Y() - b.Y()) > std::numeric_limits<int>::max())) {
            throw std::runtime_error("too big");
        }
        return static_cast<int>(std::abs(a.X() - b.X()) + std::abs(a.Y() - b.Y()));
    };

    using Node = Internal::Node;
    std::priority_queue<Node> openSet;
    std::unordered_set<AoC::Vector2D, AoC::Vector2DPosHash> closedSet;

    openSet.emplace(start, 0, heuristic(start, goal));

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.position == goal) {
            std::vector<AoC::Vector2D> path;
            int totalCost = current.gCost;
            Node* node = &current;
            while (node) {
                path.emplace_back(node->position);
                node = node->parent;
            }
            std::reverse(path.begin(), path.end());
            return {path, totalCost};
        }

        closedSet.emplace(current.position);

        for (const auto& [dx, dy] : std::vector<std::pair<int, int>>{{0, 1}, {1, 0}, {0, -1}, {-1, 0}}) {
            AoC::Vector2D neighbor = current.position + AoC::Vector2D(dx, dy);

            if (isValid(neighbor) && closedSet.find(neighbor) == closedSet.end()) {
                int newGCost = current.gCost + 1;
                int newHCost = heuristic(neighbor, goal);
                openSet.emplace(neighbor, newGCost, newHCost, new Node(current));
            }
        }
    }

    return {{}, -1};
}

uint64_t Day18::Execute1(Data data) {
    auto [path, cost] = aStar(data.map, data.start, data.goal);
    return cost;

}

std::string Day18::Execute2(Data data) {
    std::string result = "";
    for(auto corruption: data.corruptions) {
        data.map.Set(corruption,1);
        auto [path, cost] = aStar(data.map, data.start, data.goal);
        if(path.empty()) {
            result = corruption.CordRev(false);
            result.erase(0, 1);
            result.erase(result.size() - 1);
            break;
        }
    }

    return result;
}

bool Day18::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day18::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}


bool Day18::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day18::part2() {
    auto result = Execute2(m_DataB);
    return result;
}
