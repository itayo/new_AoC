#include "Day04.h"
#include <iostream>
#include <fstream>

void Day04::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    formatted.rows = raw.size();
    formatted.columns = raw[0].size();
    formatted.data = raw;
    return;
}


uint32_t Day04::Execute1(Data data) {
    uint32_t result = 0;
    std::string xmasWord = "XMAS";

    for (size_t row = 0; row < data.rows; ++row) {
        for (size_t col = 0; col < data.columns; ++col) {
            std::vector<std::string> strings(8);
            size_t id=0;
            if (row + 3 < data.rows) {
                strings[0] = {data.data[row + 0][col], data.data[row + 1][col], data.data[row + 2][col],
                              data.data[row + 3][col]};
                strings[1] = {data.data[row + 3][col], data.data[row + 2][col], data.data[row + 1][col],
                              data.data[row + 0][col]};
            }
            if (col + 3 < data.columns) {
                strings[2] = {data.data[row][col + 0], data.data[row][col + 1], data.data[row][col + 2],
                              data.data[row][col + 3]};
                strings[3] = {data.data[row][col + 3], data.data[row][col + 2], data.data[row][col + 1],
                              data.data[row][col + 0]};
            }
            if (row + 3 < data.rows && col + 3 < data.columns) {
                strings[4] = {data.data[row + 0][col + 0], data.data[row + 1][col + 1], data.data[row + 2][col + 2],
                              data.data[row + 3][col + 3]};
                strings[5] = {data.data[row + 3][col + 3], data.data[row + 2][col + 2], data.data[row + 1][col + 1],
                              data.data[row + 0][col + 0]};
            }
            if (row + 3 < data.rows && col - 3 >= 0) {
                strings[6] = {data.data[row + 0][col - 0], data.data[row + 1][col - 1], data.data[row + 2][col - 2],
                              data.data[row + 3][col - 3]};
                strings[7] = {data.data[row + 3][col - 3], data.data[row + 2][col - 2], data.data[row + 1][col - 1],
                              data.data[row + 0][col - 0]};
            }

            result += count(strings.begin(), strings.end(), xmasWord);
        }
    }

    return result;

}

uint32_t Day04::Execute2(Data data) {
    uint32_t result = 0;
    auto Valid = [&](std::string &test) {
        const std::vector<std::string> matches = {"MS", "SM"};
        return count(matches.begin(), matches.end(), test) == 1;
    };


    for (size_t row = 1; row < data.rows - 1; ++row) {
        for (size_t col = 1; col < data.columns - 1; ++col) {
            if (data.data[row][col] == 'A') {
                std::string stringA = "";
                std::string stringB = "";

                stringA += {data.data[row - 1][col - 1], data.data[row + 1][col + 1]};
                stringB += {data.data[row + 1][col - 1], data.data[row - 1][col + 1]};
                if (Valid(stringA) && Valid(stringB)) ++result;
            }

        }
    }
    return result;
}

bool Day04::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day04::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}


bool Day04::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day04::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
