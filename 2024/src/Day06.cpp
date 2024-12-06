#include "Day06.h"
#include <iostream>
#include <cassert>
#include <set>

void Day06::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    formatted.map.Reset(raw.size(), raw[0].size());
    for (size_t x = 0; x < raw.size(); ++x) {
        for (size_t y = 0; y < raw.size(); ++y) {
            if (raw[x][y] == '^' || raw[x][y] == '>' || raw[x][y] == 'v' || raw[x][y] == '<') {
                formatted.guard.Override(x, y, raw[x][y] == '^' ? AoC::Vector2D::NORTH :
                                               raw[x][y] == '>' ? AoC::Vector2D::EAST :
                                               raw[x][y] == 'v' ? AoC::Vector2D::SOUTH :
                                               AoC::Vector2D::WEST);
                formatted.map.Set(x, y, '.');


            } else formatted.map.Set(x, y, raw[x][y]);
        }
    }
    formatted.start.Override(formatted.guard);
}

void Day06::TryStep(AoC::Grid2D<char> &map, AoC::Vector2D &guard) {
    if (map.Exists(guard.LookAhead())) {
        if (map.Get(guard.LookAhead()) == 35) {
            guard.TurnRight();
            return;
        }
    }
    guard.GoForward();


}

void Day06::WalkTheWalk1(Data &data,  std::set<std::pair<size_t, size_t>> &positions) {
    auto &guard = data.guard;
    auto &map = data.map;
    guard.Override(data.start);
    while (map.Exists(guard)) {
        positions.insert({guard.X(), guard.Y()});
        TryStep(data.map, guard);
        if (data.printMap)map.PrintWithOverlay(guard);
    }
}


uint32_t Day06::Execute1(Data data) {
    std::set<std::pair<size_t, size_t>> positions;
    WalkTheWalk1(data, positions);

    return positions.size();

}

uint32_t Day06::Execute2(Data data) {
    uint32_t loops = 0;
    std::set<std::pair<size_t, size_t>> positions;
    WalkTheWalk1(data, positions);
    for (auto test: positions) {
        AoC::Grid2D<char> tmp = data.map;
        tmp.Set(test.first,test.second,'#');
        data.guard.Override(data.start);
        std::set<std::pair<std::pair<int, int>, AoC::Vector2D::tFacing>> visited_positions;
        while(tmp.Exists(data.guard)) {
            AoC::Vector2D tmpGuard = data.guard;
            TryStep(tmp,data.guard);
            std::pair<int,int> pos = {data.guard.X(),data.guard.Y()};
            auto state = std::make_pair(pos,data.guard.IsFacing());
            if(visited_positions.count(state)) {
                ++loops;
                break;
            }
            visited_positions.insert(state);
        }
    }
    return loops;
}


bool Day06::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day06::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}


bool Day06::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day06::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
