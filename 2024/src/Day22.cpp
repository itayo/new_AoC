#include "Day22.h"
#include "AoC/LinkedList.h"
#include <iostream>

void Day22::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    std::string combinedString = "";
    for (const auto &str: raw) combinedString += " " + str;
    formatted.Numbers = aoc.GetAllIntegersU64(combinedString);
    formatted.Raw = raw;

}

void Day22::Evolve(uint64_t &SIP)
{
    static auto Mix = [](uint64_t a, uint64_t b) { return a ^ b; };
    static auto Prune = [](uint64_t a) { return a % 16777216; };
    {
        uint64_t tmp = SIP * 64;
        SIP = Mix(SIP, tmp);
        SIP = Prune(SIP);
    }
    {
        uint64_t tmp = SIP / 32;
        SIP = Mix(SIP, tmp);
        SIP = Prune(SIP);
    }
    {
        uint64_t tmp = SIP * 2048;
        SIP = Mix(SIP, tmp);
        SIP = Prune(SIP);
    }

}

uint64_t Day22::Execute1(Data data) {
    uint64_t result = 0;

    for (const auto &secret: data.Numbers) {
        uint64_t SIP = secret;
        for (int i = 0; i < 2000; ++i) {
            Evolve(SIP);
        }
        result += SIP;
    }
    return result;

}

int32_t Day22::Execute2(Data data) {
    int32_t result = 0;
    std::unordered_map<std::string,int32_t > aggregated;
    auto price = [](uint64_t secret){return static_cast<int32_t>(secret%10);};
    for (const auto &secret: data.Numbers) {
        std::unordered_map<std::string,int32_t > current;
        AoC::LinkedList<int> list;
        uint64_t SIP = secret;
        auto pPrice = price(SIP);
        for (int i = 0; i < 2000; ++i) {
            Evolve(SIP);
            auto cPrice = price(SIP);
            list.push_back(cPrice - pPrice);
            pPrice = cPrice;
            while(list.size() > 4) list.pop_front();
            if(list.size() == 4) {
                const auto key = list.ToString();
                if(current.find(key) == current.end()) current[key]=cPrice;
            }

        }
        for(auto [k,v] : current) {
            if(aggregated.find(k) != aggregated.end()) aggregated[k] += v;
            else aggregated[k]=v;
        }
    }
    for(auto [k,v]: aggregated ) if(v > result) result=v;
    return result;
}

bool Day22::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day22::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}


bool Day22::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day22::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
