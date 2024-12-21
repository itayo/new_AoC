#include "Day16.h"
#include <unordered_set>
#include <queue>

void Day16::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    std::unordered_set<Internal::Position, std::hash<Internal::Position>> positionSet;
    formatted.height = raw.size();
    formatted.width = raw[0].size();
    for (int x = 0; x < formatted.height; ++x) {
        for (int y = 0; y < formatted.width; ++y) {
            switch (raw[x][y]) {
                case 'S':
                    formatted.Start = {x, y};
                    break;
                case 'E':
                    formatted.End = {x, y};
                    break;
            }
            if (raw[x][y] != '#') formatted.paths.insert({x, y});
        }
    }

}

void Day16::findLowestScore(Data &data) {
    using Element = std::pair<Internal::State, uint64_t>;
    auto cmp = [](const Element &a, const Element &b) {
        return std::get<1>(a) > std::get<1>(b);
    };
    auto inBounds = [&data](const Internal::Position &pos) {
        return pos[0] >= 0 && pos[1] >= 0 && pos[0] < data.height && pos[1] <= data.width;
    };
    std::unordered_map<Internal::State, int64_t,Internal::StateHasher> visited;
    std::priority_queue<Element, std::vector<Element>, decltype(cmp)> pq(cmp);
    Internal::State startState = {data.Start, Internal::EAST};
    visited[startState] =0;
    pq.push({startState, 0});
    while (!pq.empty()) {
        auto [state, cost] = pq.top();
        pq.pop();
        if(cost > data.cheapestCost) continue;
        if (state.pos == data.End && cost <= data.cheapestCost) {
            data.cheapestCost = cost;
        }
        auto nextGroup = state.next();
        for(auto &next:nextGroup) {
            auto &nState = next.first;
            auto &nCost = next.second;
            if(inBounds(nState.pos) && data.paths.count(nState.pos) != 0 && (visited.count(nState) ==0 || visited[nState] > cost + nCost)) {
                pq.push({nState,nCost+cost});
                visited[nState] = cost+nCost;
            }
        }
    }

}

uint64_t Day16::findLowestScore2(Data &data) {
    std::unordered_set<Internal::Position,Internal::PositionHasher> bestPaths;
    using Element = std::tuple<Internal::State, uint64_t,std::vector<Internal::Position>>;
    std::unordered_set<Internal::Position,Internal::PositionHasher> paths;
    auto cmp = [](const Element &a, const Element &b) {
        return std::get<1>(a) > std::get<1>(b);
    };
    auto inBounds = [&data](const Internal::Position &pos) {
        return pos[0] >= 0 && pos[1] >= 0 && pos[0] < data.height && pos[1] <= data.width;
    };
    std::unordered_map<Internal::State, uint64_t,Internal::StateHasher> visited;
    std::priority_queue<Element, std::vector<Element>, decltype(cmp)> pq(cmp);
    Internal::State startState = {data.Start, Internal::EAST};
    visited[startState] =0;
    pq.push({startState, 0,std::vector<Internal::Position>()});
    while (!pq.empty()) {
        auto [state, cost, path] = pq.top();
        path.emplace_back(state.pos);
        pq.pop();
        if(cost > data.cheapestCost) {
            continue;
        }
        if (state.pos == data.End && cost <= data.cheapestCost){
            for(auto p:path) bestPaths.insert(p);
                data.cheapestCost = cost;
            continue;
        }
        auto nextGroup = state.next();
        for(auto &next:nextGroup) {
            auto &nState = next.first;
            auto &nCost = next.second;
            if(inBounds(nState.pos) && data.paths.count(nState.pos) != 0 && (visited.count(nState) ==0 || visited[nState] >= cost + nCost)) {
                pq.push({nState,nCost+cost,path});
                visited[nState] = cost+nCost;
            }
        }
    }
    return bestPaths.size();

}

uint64_t Day16::Execute1(Data &data) {
    findLowestScore(data);
    uint64_t result = data.cheapestCost; //
    return result;

}

uint64_t Day16::Execute2(Data &data) {
    uint64_t result = findLowestScore2(data);
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
