#include "Day06.h"
#include <iostream>

void Day06::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    for (auto str: raw) {
        auto action = Internal::GetAction(str);
        auto vec = aoc.GetAllIntegersS32(str);
        Internal::Todo t(action, vec);
        formatted.tasks.emplace_back(t);
    }
}


uint32_t Day06::Execute1(Data data) {
    AoC::Grid2D<bool> map{1000, 1000};
    for (auto &task: data.tasks) {
        for (int i = task.from.first; i <= task.to.first; ++i) {
            for (int j = task.from.second; j <= task.to.second; ++j) {
                switch (task.whatToDo) {
                    case Internal::Action::On:
                        map.Set(i, j, true);
                        break;
                    case Internal::Action::Off:
                        map.Set(i, j, false);
                        break;
                    case Internal::Action::Toggle:
                        map.Set(i, j, !map.Get(i, j));
                        break;
                    default:
                        throw new std::runtime_error("wierd enum");
                }
            }

        }
    }
    return map.FindAllLocationsOf(true).size();
}

uint32_t Day06::Execute2(Data data) {

    int32_t result=0;
    AoC::Grid2D<int> map{1000, 1000};
    map.SetAll(0);
    for (auto &task: data.tasks) {
        for (int i = task.from.first; i <= task.to.first; ++i) {
            for (int j = task.from.second; j <= task.to.second; ++j) {
                switch (task.whatToDo) {
                    case Internal::Action::On:
                        map.Set(i, j, map.Get(i, j)+1);
                        break;
                    case Internal::Action::Off:
                        if(map.Get(i,j) > 0) {
                            map.Set(i, j, map.Get(i,j)-1);
                        }
                        break;
                    case Internal::Action::Toggle:
                        map.Set(i, j, map.Get(i, j)+2);
                        break;
                    default:
                        throw new std::runtime_error("wierd enum");
                }
            }

        }
    }
    for (size_t i = 0; i < map.Rows(); ++i) {
        for (size_t j = 0; j < map.Columns(); ++j) {
            result += map.Get(i, j);
        }
    }
    return result;
}


bool Day06::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day06::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}


bool Day06::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day06::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
