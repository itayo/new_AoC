#include "Day13.h"
#include <iostream>

void Day13::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    std::vector<std::string> tmp = raw;
    auto new_end = std::remove_if(tmp.begin(), tmp.end(), [](std::string str) { return str.empty() || str == ""; });
    tmp.erase(new_end, tmp.end());
    for (size_t i = 0; i < tmp.size() / 3; ++i) {
        auto a = aoc.GetAllIntegersU64(tmp[3 * i]);
        auto b = aoc.GetAllIntegersU64(tmp[3 * i + 1]);
        auto g = aoc.GetAllIntegersU64(tmp[3 * i + 2]);
        Internal::Game tg(a, b, g);
        formatted.games.emplace_back(tg);
    }

}


uint64_t Day13::CostIfPrice(const Internal::Game &game, uint64_t offset) {

    uint64_t Ax = game.controllerA.x;
    uint64_t Ay = game.controllerA.y;
    uint64_t Bx = game.controllerB.x;
    uint64_t By = game.controllerB.y;
    uint64_t Xt = game.goal.x + offset;
    uint64_t Yt = game.goal.y + offset;

    int64_t num1 = Xt * Ay - Yt * Ax;
    int64_t num2 = Yt * Bx - Xt * By;
    int64_t den = Bx * Ay - Ax * By;

    if (num1 % den || num2 % den)
        return 0;

    long aK = num2 / den, bK = num1 / den;

    if (aK < 0 || bK < 0) return 0;

    if (aK * Ax + bK * Bx == Xt && aK * Ay + bK * By == Yt)
        return 3 * aK + bK;
    return 0;

}

uint64_t Day13::Execute1(Data data) {
    uint64_t totalCost = 0;
    uint64_t offset = 0;

    for (const auto &game: data.games) {
        totalCost +=CostIfPrice(game, offset);
    }
     return totalCost;

}

uint64_t Day13::Execute2(Data data) {
    uint64_t totalCost = 0;
    uint64_t offset = 10000000000000;

    for (const auto &game: data.games) {
        totalCost += CostIfPrice(game, offset);

    }
    return totalCost;

}

bool Day13::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day13::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}


bool Day13::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day13::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
