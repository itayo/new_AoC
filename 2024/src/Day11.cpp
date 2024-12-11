#include "Day11.h"
#include <iostream>
#include <cassert>

void Day11::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    formatted.stones = std::move(aoc.GetAllIntegersU64(raw[0]));

}

uint64_t Day11::process_blinks(std::vector<uint64_t> &initialStones, size_t blinks) {
    uint64_t result=0;
    std::unordered_map<uint64_t, uint64_t> stoneCount;
    for (auto stone: initialStones) {
        stoneCount[stone]++;
    }
    for (size_t blink=0; blink < blinks; ++blink) {
        std::unordered_map<uint64_t, uint64_t> newCount;
        for (const auto &[stone, count]: stoneCount) {
            auto newStones = process_stone(stone, count);
            for (const auto &[nStone, nCount]: newStones) {
                newCount[nStone] += nCount;
            }
        }
        stoneCount = std::move(newCount);
    }
    for(const auto& [stone, count ]: stoneCount) result +=count;
    return result;
}

std::unordered_map<uint64_t, uint64_t> Day11::process_stone(uint64_t stone, uint64_t count) {
    std::unordered_map<uint64_t, uint64_t> newCount;
    if(stone == 0) newCount[1] +=count;
    else {
        std::string digits= std::to_string(stone);
        if(digits.length()%2 == 0) {
            size_t mid = digits.length()/2;
            uint64_t left = std::stoull(digits.substr(0,mid));
            uint64_t right = std::stoull(digits.substr(mid));
            newCount[left]+= count;
            newCount[right]+= count;
        } else
            newCount[stone*2024]+=count;
    }
    return newCount;
}

uint64_t Day11::Execute1(Data data) {
    return process_blinks(data.stones, 25);

}


uint64_t Day11::Execute2(Data data) {
    return process_blinks(data.stones, 75);
}

bool Day11::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day11::part1() {
    auto result = Execute1(m_DataA);
    if (result != 233875)
        throw std::runtime_error(
                std::string("Wrong result: ").append(std::to_string(result).append(" instead of 233875")));
    return std::to_string(result);
}


bool Day11::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day11::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
