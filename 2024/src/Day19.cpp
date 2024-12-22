#include "Day19.h"
#include <iostream>
#include <unordered_set>

void Day19::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    auto towelsStr = raw[0];
    aoc.StringReplace(towelsStr,{{" ",""}});
    formatted.towels = aoc.StringSplit(towelsStr,',');
    for(size_t i=2;i< raw.size();++i) {
        formatted.designs.emplace_back(raw[i]);
    }
    std::sort(formatted.towels.begin(),formatted.towels.end(),[]
            (const std::string& first, const std::string& second){
        return first.size() > second.size();
    });
    formatted.maxTowelLength = formatted.towels.begin()->size();

}

uint64_t Day19::Execute1(Data data) {
    std::vector<std::string> result;
    std::ostringstream oss;
    for (size_t i = 0; i < data.towels.size(); ++i) {
        if (i > 0) {
            oss << "|";
        }
        oss << data.towels[i];
    }
    std::string regexPattern = "^(" + oss.str() + ")+$";
    std::regex pattern(regexPattern);
    for (const auto& sut : data.designs) {
        if (std::regex_match(sut, pattern)) result.emplace_back(sut);
    }
    return result.size();

}
uint64_t Day19::CanBeRebuiltTester(const std::string sut, const Data &data, const size_t depth,std::unordered_map<std::string, uint64_t> &cacher) {
    uint64_t count = 0;
    if (sut.empty()) return 1;

    for (size_t i = data.maxTowelLength; i >= 1; i--) {
        if (sut.size() < i) continue;
        if (std::find(data.towels.begin(), data.towels.end(),sut.substr(0,i)) != data.towels.end()) {
            const auto remainingString = sut.substr(i, sut.size() - i);
            if (cacher.count(remainingString) == 0) {
                cacher[remainingString] = CanBeRebuiltTester(remainingString, data, depth + 1, cacher);
            }
            count += cacher[remainingString];
        }
    }
    return count;
}

uint64_t Day19::Execute2(Data data) {
    uint64_t result=0;
    std::unordered_map<std::string, uint64_t> cacher;
    for(auto design:data.designs) {
        result+=CanBeRebuiltTester(design,data,0,cacher);
    }
    return result;
}

bool Day19::testPart1() {
    auto result=Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day19::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}



bool Day19::testPart2() {
    auto result=Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day19::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
