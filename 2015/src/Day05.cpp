#include "Day05.h"
#include <iostream>

void Day05::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    formatted.strings = std::move(raw);

}

uint32_t Day05::Execute1(Data data) {
    uint32_t result = 0;
    static const std::vector<std::string> forbidden = {"ab", "cd", "pq", "xy"};
    static const std::vector<std::string> vowels = {"a", "e", "i", "o", "u"};

    for (auto string: data.strings) {
        int32_t vowelsCount = 0;
        bool forbiddenFound = false;
        bool doubleCharFound = false;
        char lastCharacter = 0;
        for (auto &vowel: vowels) {
            size_t nPos = string.find(vowel, 0);
            while (nPos != std::string::npos) {
                ++vowelsCount;
                nPos = string.find(vowel, nPos + vowel.size());
            }
        }
        if (vowelsCount < 3) continue;
        for (auto &forbiddenWord: forbidden) {
            size_t nPos = string.find(forbiddenWord, 0);
            if (nPos != std::string::npos) {
                forbiddenFound = true;
                break;
            }
        }
        if (forbiddenFound) continue;
        for (auto &chr: string) {
            if (lastCharacter == chr) {
                doubleCharFound = true;
                break;
            }
            lastCharacter = chr;
        }
        if (!doubleCharFound) continue;
        ++result;

    }
    return result;

}

uint32_t Day05::Execute2(Data data) {
    uint32_t result = 0;

    for (auto &string: data.strings) {
        bool hasDoubles = false;
        bool hasRepetition = false;
        for (size_t i = 0; i < string.size() - 2; ++i) {
            char &a = string[i];
            char &b = string[i + 2];
            if (a == b) {
                hasDoubles = true;
                break;
            }
        }
        if (!hasDoubles) continue;
        for (size_t i = 0; i < string.size() - 3; ++i) {
            std::string a = string.substr(i, 2);
            for (size_t j = i + 2; j < string.size() - 1; ++j) {
                std::string b = string.substr(j, 2);
                if (a == b) {
                    hasRepetition = true;
                    break;
                }
            }

        }
        if(hasDoubles && hasRepetition) ++result;
    }
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
