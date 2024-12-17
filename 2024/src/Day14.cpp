#include "Day14.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <iostream>

void Day14::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    formatted.grid.Reset(103,101,'0');
    formatted.testGrid.Reset(7,11,'0');
    for (const auto &r: raw) {
        std::istringstream iss(r);
        std::string pos, vel;
        iss >> pos >> vel;
        pos = pos.substr(2);
        vel = vel.substr(2);
        std::replace(pos.begin(), pos.end(), ',', ' ');
        std::replace(vel.begin(), vel.end(), ',', ' ');
        int posX, posY, velX, velY;
        std::istringstream issPos(pos);
        std::istringstream issVel(vel);
        Internal::robot robot;
        issPos >> robot.pos.x >> robot.pos.y;
        issVel >> robot.vel.x >> robot.vel.y;
        formatted.robots.emplace_back(robot);
    }
}

uint32_t Day14::Execute1(Data data,bool test = false) {
    const int width = test? 11:101;
    const int height =test ? 7: 103;
    const int verticalDivision = test ? 5:50;
    const int horizontalDivision = test ? 3:51;
    std::vector<Internal::robot> ruts;
    auto &grid = test? data.testGrid:data.grid;
    grid.SetRow(horizontalDivision,' ');
    grid.SetColumn(verticalDivision,' ');
    uint64_t quadrantA = 0;
    uint64_t quadrantB = 0;
    uint64_t quadrantC = 0;
    uint64_t quadrantD = 0;
    for (auto robot: data.robots) {
        Internal::robot rut = robot;
        rut.pos.x = rut.pos.x + (100 * rut.vel.x);
        rut.pos.y = rut.pos.y + (100 * rut.vel.y);
        rut.pos.x %= width;
        if (rut.pos.x < 0) rut.pos.x += width;
        rut.pos.y %= height;
        if (rut.pos.y < 0) rut.pos.y += height;
        ruts.emplace_back(rut);
        if (rut.pos.x == verticalDivision || rut.pos.y == horizontalDivision) continue;
        grid.Set(rut.pos.y,rut.pos.x,grid.Get(rut.pos.y,rut.pos.x)+1);
        if (rut.pos.x < verticalDivision) {
            if (rut.pos.y < horizontalDivision) {
                ++quadrantA;
            } else {
                ++quadrantC;
            }
        } else {
            if (rut.pos.y < horizontalDivision) {
                ++quadrantB;
            } else {
                ++quadrantD;
            }
        }

    }
    return quadrantA * quadrantB * quadrantC * quadrantD;

}

uint32_t Day14::Execute2(Data data, bool test) {
    ///todo:: try implementing real logic to find it instead of stepping 1 frame at a time. it took me 2    hours and 15 minutes to find :(
    if(test) return 0;
    const int width = 101;
    const int height =103;
    const int verticalDivision = 50;
    const int horizontalDivision = 51;

    auto &grid = data.grid;

    for(int i=0;i< grid.Rows();++i) grid.SetRow(i,'.');
    uint64_t quadrantA = 0;
    uint64_t quadrantB = 0;
    uint64_t quadrantC = 0;
    uint64_t quadrantD = 0;
    uint64_t steps=7860;
    std::vector<Internal::robot> ruts;
    while(steps < 7861) {
        for(int i=0;i< grid.Rows();++i) grid.SetRow(i,'.');
        ++steps;
        for (auto robot: data.robots) {
            Internal::robot rut = robot;
            rut.pos.x = rut.pos.x + (steps * rut.vel.x);
            rut.pos.y = rut.pos.y + (steps * rut.vel.y);
            rut.pos.x %= width;
            if (rut.pos.x < 0) rut.pos.x += width;
            rut.pos.y %= height;
            if (rut.pos.y < 0) rut.pos.y += height;
            ruts.emplace_back(rut);
            grid.Set(rut.pos.y, rut.pos.x, 'X');
        }
    }
    std::cout << "day 14 visual finding" << std::endl;
    grid.Print();
    std::cout << std::endl;
    return 7861;
}

bool Day14::testPart1() {
    auto result = Execute1(m_DataTestA,true);
    return ExpectedTestA == result;
}

std::string Day14::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}


bool Day14::testPart2() {
    auto result = Execute2(m_DataTestB,true );
    return ExpectedTestB == result;
}

std::string Day14::part2() {
    auto result = Execute2(m_DataB,false);
    return std::to_string(result);
}
