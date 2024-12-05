#include "Day05.h"
#include <iostream>
#include <cassert>

void Day05::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    size_t idx = 0;
    for (; idx < raw.size() && raw[idx] != ""; ++idx) {
        std::vector<int> rule = std::move(aoc.GetAllIntegersS32(raw[idx]));
        formatted.ShouldBeBeforeRule[rule[0]].emplace_back(rule[1]);
        formatted.ShouldBeAfterRule[rule[1]].emplace_back(rule[0]);
        formatted.Rules.push_back({rule[0], rule[1]});

    }
    ++idx;
    for (; idx < raw.size(); ++idx) {
        auto vec = std::move(aoc.GetAllIntegersS32(raw[idx]));

        assert(vec.size() % 2 == 1);
        formatted.PageOrders.emplace_back(true, std::move(vec));
    }
    return;

}

bool Day05::CheckIfGood(std::vector<int32_t> pages, Data data) {
    for (size_t idx = 0; idx < pages.size(); ++idx) {
        auto &page = pages[idx];
        auto beforeTest = data.ShouldBeBeforeRule.find(page);
        auto afterTest = data.ShouldBeAfterRule.find(page);

        if (beforeTest != data.ShouldBeBeforeRule.end()) {
            for (auto &test: beforeTest->second) {
                auto myIdx = pages.begin() + idx;
                if (std::find(pages.begin(), myIdx, test) != myIdx) {
                    return false;
                }
            }
        }

        if (afterTest != data.ShouldBeAfterRule.end()) {
            for (auto &test: afterTest->second) {
                auto myIdx = pages.begin() + idx;
                if (std::find(myIdx, pages.end(), test) != pages.end()) {
                    return false;
                }
            }
        }

    }
    return true;
}

void Day05::SortGoodOrBad(Day05::Data &data) {
    for (auto &pageOrder: data.PageOrders) {
        for (size_t idx = 0; idx < pageOrder.pages.size(); ++idx) {
            auto &pages = pageOrder.pages;
            pageOrder.isGood = CheckIfGood(pages, data);
        }
    }
}


uint32_t Day05::Execute1(Data data) {
    uint32_t result = 0;
    SortGoodOrBad(data);
    auto GoodPrints = std::move(GetPrints(data, true));

    for (auto &GoodPrint: GoodPrints) {
        result += GoodPrint.pages[GoodPrint.pages.size() / 2];
    }

    return result;

}

uint32_t Day05::Execute2(Data data) {
    uint32_t result = 0;
    bool swapped = false;
    SortGoodOrBad(data);
    auto BadPrints = std::move(GetPrints(data, false));
    for (auto &badPrint: BadPrints) {
        auto &pages = badPrint.pages;
        std::vector<std::pair<int, int>> ValidRules;
        for (int i = 0; i < pages.size() - 1; ++i) {
            for (int j = 1; j < pages.size(); ++j) {
                auto &a = pages[i];
                auto &b = pages[j];
                std::copy_if(data.Rules.begin(), data.Rules.end(), std::back_inserter(ValidRules),
                             [&a, &b](std::pair<int, int> obj) {
                                 return (obj.first == a && obj.second == b) || (obj.first == b && obj.second == a);
                             });

            }
        }
        while (!CheckIfGood(pages, data)) {
            for (auto rule: ValidRules) {
                auto a = std::distance(pages.begin(), std::find(pages.begin(), pages.end(), rule.first));
                auto b = std::distance(pages.begin(), std::find(pages.begin(), pages.end(), rule.second));
                if (a > b) std::swap(pages[a], pages[b]);

            }
        };
    }
    for (auto &b: BadPrints) result += b.pages[b.pages.size() / 2];

    return result;

}

bool Day05::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day05::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}


bool Day05::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day05::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
