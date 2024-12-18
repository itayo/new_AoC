#include "Day15.h"
#include "AoC/Vector2D.h"
#include <iostream>
#include <set>
#include <queue>

void Day15::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    auto &smallObjects = formatted.smallObjects;
    auto &smallPlayer = formatted.smallPlayer;
    auto &smallMap = formatted.smallMap;
    auto &commands = formatted.commands;
    auto &bigPlayer = formatted.bigPlayer;
    auto &bigMap = formatted.bigMap;

    std::vector<std::string> rawCommands;
    std::vector<std::string> rawMap;
    auto iter = std::find_if(raw.begin(), raw.end(), [](std::string r) { return r == ""; });
    std::copy(raw.begin(), iter, std::back_inserter(rawMap));
    std::copy(iter + 1, raw.end(), std::back_inserter(rawCommands));
    smallMap.Reset(rawMap.size(), rawMap[0].size(), '.');
    formatted.raw.first = rawMap;
    formatted.raw.second = rawCommands;
    bigMap.Reset(rawMap.size(), rawMap[0].size() * 2, '.');
    for (size_t x = 0; x < rawMap.size(); ++x) {
        for (size_t y = 0; y < rawMap[x].size(); ++y) {
            if (rawMap[x][y] == 'O') {
                smallObjects.emplace_back(AoC::Vector2D(x, y));
                bigMap.Set(x, (2 * y), '[');
                bigMap.Set(x, (2 * y) + 1, ']');
            } else if (rawMap[x][y] == '@') {
                bigMap.Set(x, (2 * y), '.');
                bigMap.Set(x, (2 * y) + 1, '.');
                smallPlayer.Override(x, y, AoC::Vector2D::NORTH);
                bigPlayer.Override(x, 2 * y, AoC::Vector2D::NORTH);
            } else if (rawMap[x][y] == '#') {
                smallMap.Set(x, y, rawMap[x][y]);
                bigMap.Set(x, (2 * y), '#');
                bigMap.Set(x, (2 * y) + 1, '#');
            }
        }
    }
    for (size_t x = 0; x < rawCommands.size(); ++x) {
        for (size_t y = 0; y < rawCommands[x].size(); ++y) {
            switch (rawCommands[x][y]) {
                case '<':
                    commands.emplace_back(AoC::Vector2D(0, -1, AoC::Vector2D::tFacing::WEST));
                    break;
                case '>':
                    commands.emplace_back(AoC::Vector2D(0, 1, AoC::Vector2D::tFacing::EAST));
                    break;
                case '^':
                    commands.emplace_back(AoC::Vector2D(-1, 0, AoC::Vector2D::tFacing::NORTH));
                    break;
                case 'v':
                    commands.emplace_back(AoC::Vector2D(1, 0, AoC::Vector2D::tFacing::SOUTH));
                    break;
                default:
                    throw new std::runtime_error("unexpected character");
            }

        }
    }

}

uint64_t Day15::Execute1(Data data) {
    uint64_t result = 0;
    auto &objects = data.smallObjects;
    auto &player = data.smallPlayer;
    auto &map = data.smallMap;
    auto &commands = data.commands;
    size_t before = map.FindAllLocationsOf('[').size();
    for (const auto &command: commands) {
        bool blocked = false;
        std::vector<std::vector<AoC::Vector2D>::iterator> objs;
        player.SetFacing(command.IsFacing());
        auto ahead = player.LookAhead();
        for (auto &object: objects) object.SetFacing(command.IsFacing());
        auto iter = std::find_if(objects.begin(), objects.end(),
                                 [ahead](AoC::Vector2D object) { return object == ahead; });
        if (map.Get(player.LookAhead()) == '#') blocked = true;
        while (iter != objects.end() && !blocked) {
            if (map.Get(iter->LookAhead()) == '#') {
                blocked = true;
                continue;
            }
            objs.emplace_back(iter);
            ahead = iter->LookAhead();
            iter = std::find_if(objects.begin(), objects.end(),
                                [ahead](AoC::Vector2D object) { return object == ahead; });
        }
        if (not blocked) {
            player.GoForward();
            for (auto it: objs) it->GoForward();
        }


    }
    for (auto obj: objects) {
        result += ((100 * obj.X()) + obj.Y());
    }

    return result;
}

uint64_t Day15::Execute2(Data data) {
    uint64_t result = 0;
    auto &map = data.bigMap;
    auto &player = data.bigPlayer;
    auto &commands = data.commands;
    for (auto &command: commands) {
        player.SetFacing(command.IsFacing());
        if (map.Get(player.LookAhead()) == '.') {
            player.GoForward();
            continue;
        }
        if (command.Y() != 0) {
            std::queue<AoC::Vector2D> queue;
            std::map<AoC::Vector2D, char> visited;
            visited[player + command] = map.Get(player + command);
            queue.emplace(player);
            while (!queue.empty()) {
                auto curr = queue.front();
                queue.pop();
                auto peek = curr + command;
                const auto &peekC = map.Get(peek);
                if (peekC == '#') {
                    visited.clear();
                    break;
                }
                if (peekC == '.') continue;
                visited[peek] = peekC;
                if (peekC == '[') {
                    queue.emplace(peek.X(), peek.Y() + 1);
                    AoC::Vector2D d(peek.X(), peek.Y() + 1);
                    visited[d] = map.Get(d);
                }
                if (peekC == ']') {
                    queue.emplace(peek.X(), peek.Y() - 1);
                    AoC::Vector2D d(peek.X(), peek.Y() - 1);
                    visited[d] = map.Get(d);
                }

            }
            for (auto [pos, val]: visited) {
                map.Set(pos , '.');
            }
            for (auto [pos, val]: visited) {
                map.Set(pos + command, val);
            }

            if (!visited.empty()) player.GoForward();
        } else {
            std::queue<AoC::Vector2D> queue;
            std::map<AoC::Vector2D, char> visited;
            visited[player + command] = map.Get(player + command);
            queue.emplace(player);
            while (!queue.empty()) {
                auto curr = queue.front();
                queue.pop();
                auto peek = curr + command;
                const auto &peekC = map.Get(peek);
                if (peekC == '#') {
                    visited.clear();
                    break;
                }
                if (peekC == '.') continue;
                visited[peek] = peekC;
                if (peekC == '[') {
                    queue.emplace(peek);
                    queue.emplace(peek.X(), peek.Y() + 1);
                    AoC::Vector2D d(peek.X(), peek.Y() + 1);
                    visited[d] = map.Get(d);
                }
                if (peekC == ']') {
                    queue.emplace(peek);
                    queue.emplace(peek.X(), peek.Y() - 1);
                    AoC::Vector2D d(peek.X(), peek.Y() - 1);
                    visited[d] = map.Get(d);
                }

            }
            for (auto [pos, val]: visited) {
                map.Set(pos , '.');
            }
            for (auto [pos, val]: visited) {
                map.Set(pos + command, val);
            }

            if (!visited.empty()) player.GoForward();

        }

    }
    auto test = map.FindAllLocationsOf('[');
    for(auto t:test) result += (100*t.X())+t.Y();
    return result;
}

bool Day15::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day15::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}


bool Day15::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day15::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
