#include "Day08.h"
#include <iostream>

void Day08::PrepareData(std::vector<std::string> &raw, Data &formatted) {

    formatted.X = raw.size();
    formatted.Y = raw[0].size();
    for (int x = 0; x < raw.size(); ++x) {
        for (int y = 0; y < raw[0].size(); ++y) {
            if (raw[x][y] == '.') continue;
            formatted.antennas[raw[x][y]].emplace_back(x, y);
        }

    }
}

uint32_t Day08::Execute1(Data data) {
    int result = 0;
    std::set<std::pair<int,int>> anti;
    const auto &maxX= data.X;
    const auto &maxY = data.Y;
    auto in_range= [&maxX,maxY](int x, int y) -> bool{
        return x >= 0 && y >= 0 && x < maxX && y < maxY;

    };
    for (auto &antenna: data.antennas) {

        auto &position = antenna.second;
        for (int i = 0; i < position.size() - 1; i++) {
            for (int j = i + 1; j < position.size(); j++) {
                auto &a = position[i];
                auto &b = position[j];
                std::pair<int, int> diff = {b.first - a.first, b.second - a.second};
                std::pair<int, int> first{a.first - diff.first, a.second - diff.second};
                std::pair<int, int> second{b.first + diff.first, b.second + diff.second};
                if (in_range(first.first, first.second))
                    anti.insert({first.first, first.second});
                if (in_range(second.first, second.second))
                    anti.insert({second.first, second.second});
            }
        }
    }
    return anti.size();
}

uint32_t Day08::Execute2(Data data) {
    int result = 0;
    std::set<std::pair<int,int>> anti;
    const auto &maxX= data.X;
    const auto &maxY = data.Y;
    auto in_range= [&maxX,maxY](int x, int y) -> bool{
        return x >= 0 && y >= 0 && x < maxX && y < maxY;

    };
    for (auto &antenna: data.antennas) {

        auto &position = antenna.second;
        for (int i = 0; i < position.size() - 1; i++) {
            for (int j = i + 1; j < position.size(); j++) {
                auto &a = position[i];
                auto &b = position[j];
                std::pair<int, int> diff = {b.first - a.first, b.second - a.second};
                std::pair<int, int> first{a.first, a.second };
                std::pair<int, int> second{b.first , b.second };
                while (in_range(first.first, first.second)) {
                    anti.insert({first.first, first.second});
                    first = {first.first - diff.first,first.second - diff.second};
                }
                while (in_range(second.first, second.second)) {
                    anti.insert({second.first, second.second});
                    second = {second.first + diff.first,second.second + diff.second};
                }
            }
        }
    }
    return anti.size();
}


bool Day08::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day08::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}


bool Day08::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day08::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
