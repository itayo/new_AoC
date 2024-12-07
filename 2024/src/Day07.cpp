#include "Day07.h"
#include <iostream>

void Day07::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    for (auto &row: raw) {
        std::vector<uint64_t> vec = aoc.GetAllIntegersU64(row);
        Data::tPart part;
        part.expected = vec[0];
        for (size_t i = 1; i < vec.size(); ++i) {
            part.parts.emplace_back(vec[i]);
        }
        formatted.parts.emplace_back(part);

    }

}

uint64_t Day07::Execute1(Data data) {
    uint64_t result = 0;
    for (auto &part: data.parts) {
        auto &expected = part.expected;
        auto &parts = part.parts;
        std::vector<uint64_t> results;
        results.emplace_back(parts[0]);
        for (size_t i = 1; i < parts.size(); ++i) {
            std::vector<uint64_t> tmps;
            std::swap(tmps, results);
            for (const auto &tmp: tmps) {
                if ((tmp + parts[i]) <= part.expected) results.emplace_back(tmp + parts[i]);
                if ((tmp * parts[i]) <= part.expected)results.emplace_back(tmp * parts[i]);
            }
        }
        if (std::find(results.begin(), results.end(), part.expected) != results.end()) {
            result += part.expected;
        }
    }
    return result;
}

uint64_t Day07::Execute2(Data data) {
    uint64_t result = 0;
    for (auto &part: data.parts) {
        auto &expected = part.expected;
        auto &parts = part.parts;
        std::vector<uint64_t> results;
        results.emplace_back(parts[0]);
        for (size_t i = 1; i < parts.size(); ++i) {
            std::vector<uint64_t> tmps;
            std::swap(tmps, results);
            for (const auto &tmp: tmps) {

                auto a = tmp + parts[i];
                auto b = tmp * parts[i];
                auto c = Internal::concatenate(tmp, parts[i]);
                if (a<= part.expected)results.emplace_back(a);
                if (b <= part.expected)results.emplace_back(b);
                if (c <= part.expected)results.emplace_back(c);
            }
        }
        if (std::find(results.begin(), results.end(), part.expected) != results.end()) {
            result += part.expected;
        }
    }
    return result;
}


bool Day07::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day07::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}


bool Day07::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day07::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
