#include "Day03.h"
#include <iostream>

void Day03::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    formatted.data = raw[0];
}

uint32_t Day03::Execute1(Data data) {
    uint32_t result = 0;
    AoC::Vector2D santa;
    std::unordered_map<AoC::Vector2D, int, AoC::Vector2DHash> locations{{santa, 1}};

    ChristmasMover MoveSanta = {
            {'^', [&santa]() { santa.GoNorth(); }},
            {'<', [&santa]() { santa.GoWest(); }},
            {'v', [&santa]() { santa.GoSouth(); }},
            {'>', [&santa]() { santa.GoEast(); }},
    };

    for (const auto& dir : data.data) {
        if (MoveSanta.find(dir) != MoveSanta.end()) {
            MoveSanta.at(dir)();
            locations[santa]++;
        } else {
            throw std::runtime_error(std::string("Unexpected character detected: ") + dir);
        }
    }

    // The number of unique locations is the size of the map
    return locations.size();
}

uint32_t Day03::Execute2(Data data) {
    uint32_t result = 0;
    AoC::Vector2D santa(0,0),robot(0, 0);
    std::unordered_map<AoC::Vector2D, int, AoC::Vector2DHash> locations{{santa, 1}};
    bool moveSanta=false;

    ChristmasMover MoveSanta = {
            {'^', [&santa]() { santa.GoNorth(); }},
            {'<', [&santa]() { santa.GoWest(); }},
            {'v', [&santa]() { santa.GoSouth(); }},
            {'>', [&santa]() { santa.GoEast(); }},
    };

    ChristmasMover MoveRobot = {
            {'^', [&robot]() { robot.GoNorth(); }},
            {'<', [&robot]() { robot.GoWest(); }},
            {'v', [&robot]() { robot.GoSouth(); }},
            {'>', [&robot]() { robot.GoEast(); }},
    };
    MoveSelector mover = {{false, MoveSanta},{true,MoveRobot}};
    UpdateSelector updater = {  {false, [&santa,&locations]() { locations[santa]++; }},
                                {true, [&robot,&locations]() { locations[robot]++; }},};


    for (const auto& dir : data.data) {
        if (mover[moveSanta].find(dir) != mover[moveSanta].end()) {
            mover[moveSanta].at(dir)();
            updater[moveSanta]();
            moveSanta = moveSanta ? false:true;
        } else {
            throw std::runtime_error(std::string("Unexpected character detected: ") + dir);
        }
    }

    // The number of unique locations is the size of the map
    return locations.size();
}

bool Day03::testPart1() {
    auto result=Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day03::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}



bool Day03::testPart2() {
    auto result=Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day03::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
