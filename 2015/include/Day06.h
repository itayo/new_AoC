#ifndef DAY06_H
#define DAY06_H

#include "DayBase.h"
#include "AoC/Grid2D.h"
#include <string>
#include <AoC/aoc.h>
#include <cassert>


class Day06 : public DayBase {
public:
    Day06() {
        m_rawDataA = aoc.ReadFile("Data/input06A.txt");
        m_rawDataB = aoc.ReadFile("Data/input06B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input06A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input06B.txt");
        PrepareData();
    }


    std::string part1() override;

    std::string part2() override;

    bool testPart1() override;

    bool testPart2() override;

private:

    class Internal {
    public:
        void none(){};
        enum class Action {
            On,
            Off,
            Toggle
        };
        static Action GetAction(const std::string &action) {
            if(action.substr(0,7)== "turn on") return Action::On;
            else if(action.substr(0,8) == "turn off") return Action::Off;
            else if(action.substr(0,6) == "toggle") return Action::Toggle;
            else (assert(false));
            return Action::Off;
        }
        struct Todo {
            explicit Todo(Action a,std::vector<int> v) {
                whatToDo =a;
                from = {v[0],v[1]};
                to= {v[2], v[3]};
            }
            Action whatToDo;
            std::pair <int,int> from;
            std::pair <int,int> to;
        };
        //defineDayFunctions
    };
    struct Data {
        std::vector<Internal::Todo> tasks;

    };
    const uint32_t ExpectedTestA = 998996;
    const uint32_t ExpectedTestB = 2000000;

    AoC::AoC aoc;
    std::vector<std::string> m_rawDataA;
    std::vector<std::string> m_rawDataB;
    std::vector<std::string> m_rawDataTestA;
    std::vector<std::string> m_rawDataTestB;
    Data m_DataA;
    Data m_DataB;
    Data m_DataTestA;
    Data m_DataTestB;

    void PrepareData() {
        PrepareData(m_rawDataA, m_DataA);
        PrepareData(m_rawDataA, m_DataB);
        PrepareData(m_rawDataTestA, m_DataTestA);
        PrepareData(m_rawDataTestB, m_DataTestB);
    }

    void PrepareData(std::vector<std::string> &raw, Data &formatted);

    uint32_t Execute1(Data data);

    uint32_t Execute2(Data data);
};


#endif // DAY06_H
