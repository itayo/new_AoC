#include "Day21.h"
#include <iostream>
#include <queue>
#include <AoC/Position.h>
#include <string_view>

void Day21::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    formatted.Raw = raw;

}

AoC::Position Day21::FindLocation(char c, const std::vector<std::string> &KEYPAD) {
    for (int x = 0; x < KEYPAD.size(); ++x) {
        for (int y = 0; y < KEYPAD[x].size(); ++y) {
            if (KEYPAD[x][y] == c) return {x, y};
        }
    }
    return {-1, -1};

}

void Day21::CacheShortestSequence(char fromKey, char toKey, const std::vector<std::string> &KEYPAD,
                                  Data::AllPathsMap &paths) {
    auto fromPos = FindLocation(fromKey, KEYPAD);
    auto toPos = FindLocation(toKey, KEYPAD);
    int32_t manhattanDistance = std::abs(fromPos[0] - toPos[0]) + std::abs(fromPos[1] - toPos[1]);
    std::queue<std::pair<AoC::Position, std::string>> q;
    q.emplace(fromPos, "");
    while (!q.empty()) {
        auto [pos, path] = q.front();
        q.pop();
        if (pos == toPos) {
            paths[{fromKey, toKey}].emplace_back(path + "A");
        }
        if (path.length() >= manhattanDistance) continue;
        for (auto dir: AoC::Position::AllDirs()) {
            auto nextPos = pos + dir.first;
            auto &x = nextPos[0];
            auto &y = nextPos[1];
            if (x >= 0 && x < KEYPAD.size() &&
                y >= 0 && y < KEYPAD[x].size() &&
                KEYPAD[x][y] != ' ') {
                q.emplace(nextPos, path + dir.second);
            }
        }
    }
}


void Day21::CacheAllShortestSequences(const std::vector<std::string> &KEYPAD, Data::AllPathsMap &Paths) {
    std::string combinedString;
    for (const auto &str: KEYPAD) combinedString += str;
    for (const char &a: combinedString) {
        for (const char &b: combinedString) {
            if (a == '#' && b == '#') continue;
            if (a == b) {
                Paths[{a, b}] = {"A"};
                continue;
            }
            CacheShortestSequence(a, b, KEYPAD, Paths);
        }
    }
}

void Day21::CacheAllShortestSequences(Day21::Data &data) {
    CacheAllShortestSequences(data.NumericalKeyboard, data.NumericalPaths);
    CacheAllShortestSequences(data.DirectionalKeyboard, data.DirectionalPaths);

}

std::string Day21::combinePart1(std::string codeStr, Data &data, int layer, int directionalRobots) {
    if (layer > directionalRobots) return codeStr;
    std::string sequence = "";
    char previous = 'A';
    auto paths = layer > 0 ? data.DirectionalPaths : data.NumericalPaths;
    for (auto &current: codeStr) {
        std::string best = "";
        std::vector<std::string> seqs = paths[{previous, current}];
        for (auto seq: seqs) {
            auto test = combinePart1(seq, data, layer + 1, directionalRobots);
            if (best == "" || test.length() < best.length()) {
                best = test;
            }
        }
        sequence += best;

        previous = current;

    }

    return sequence;
}

uint64_t Day21::combinePart2(std::string codeStr, Data &data, int layer, int directionalRobots,
                             std::unordered_map<std::pair<std::string, int>, uint64_t, GenericHasher> &memory) {
    std::pair<std::string, int> key = {codeStr, layer};
    if (memory.find(key) != memory.end()) {
        return memory[{codeStr, layer}];
    }
    if (layer > directionalRobots) {
        memory[key] = codeStr.length();
        return codeStr.length();
    }
    uint64_t best = 0;
    char previous = 'A';
    auto &paths = layer > 0 ? data.DirectionalPaths : data.NumericalPaths;
    for (auto &current: codeStr) {
        uint64_t currentBest = std::numeric_limits<uint64_t>::max();
        std::vector<std::string> seqs = paths[{previous, current}];
        for (auto seq: seqs) {
            auto test = combinePart2(seq, data, layer + 1, directionalRobots, memory);
            if (currentBest == std::numeric_limits<uint64_t>::max() || test < currentBest) {
                currentBest = test;
            }
        }
        best += currentBest;

        previous = current;

    }
    memory[key] = best;
    return best;
}


uint64_t Day21::Execute1(Data &data) {
    uint64_t result = 0;
    CacheAllShortestSequences(data);
    for (auto code: data.Raw) {
        uint64_t codeNum = std::stoull(code);
        std::string combined = combinePart1(code, data, 0, 2);
        result += (codeNum * combined.length());
    }
    return result;
}

uint64_t Day21::Execute2(Data &data) {
    uint64_t result = 0;
    CacheAllShortestSequences(data);
    std::unordered_map<std::pair<std::string, int>, uint64_t, GenericHasher> memory;
    for (auto code: data.Raw) {
        uint64_t codeNum = std::stoull(code);
        uint64_t combined = combinePart2(code, data, 0, 25, memory);
        result += (codeNum * combined);
    }
    return result;
}

bool Day21::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day21::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}


bool Day21::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day21::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
