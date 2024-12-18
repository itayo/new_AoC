#include "DayBase.h"
#include "DayExecutor.h"
#include "TestData.h"
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include "fort.h"
#include "Day01.h"
#include "Day02.h"
#include "Day03.h"
#include "Day04.h"
#include "Day05.h"
#include "Day06.h"
#include "Day07.h"
#include "Day08.h"
#include "Day09.h"
#include "Day10.h"
#include "Day11.h"
#include "Day12.h"
#include "Day13.h"
#include "Day14.h"
#include "Day15.h"
#include "Day16.h"
//DayHeader

struct DayInfo {
    std::unique_ptr<DayBase> day;
    std::string Name;
    bool hasRun = false;
    bool TestAPass = false;
    bool TestBPass = false;
    double executionTimeA;
    std::string codeA;
    double executionTimeB;
    std::string codeB;

};

std::vector<DayInfo> createDays() {
    std::vector<DayInfo> days;
    /*days.push_back({std::make_unique<Day01>(), "01"});
    days.push_back({std::make_unique<Day02>(), "02"});
    days.push_back({std::make_unique<Day03>(), "03"});
    days.push_back({std::make_unique<Day04>(), "04"});
    days.push_back({std::make_unique<Day05>(), "05"});
    days.push_back({std::make_unique<Day06>(), "06"});
    days.push_back({std::make_unique<Day07>(), "07"});
    days.push_back({std::make_unique<Day08>(), "08"});
    days.push_back({std::make_unique<Day09>(), "09"});
    days.push_back({std::make_unique<Day10>(), "10"});
    days.push_back({std::make_unique<Day11>(), "11"});
    days.push_back({std::make_unique<Day12>(), "12"});
    days.push_back({std::make_unique<Day13>(), "13"});
    days.push_back({std::make_unique<Day14>(), "14"});
    days.push_back({std::make_unique<Day15>(), "15"});*/
    days.push_back({std::make_unique<Day16>(), "16"});
    //dayCreator
    return days;
}


DayInfo &findDayByName(std::vector<DayInfo> &days, const std::string name) {
    std::string finalName = name;
    if (name.length() == 1 && std::isdigit(name[0])) {
        finalName = "0" + name;  // Add a leading zero if it's a single-digit number
    }
    auto it = std::find_if(days.begin(), days.end(), [&finalName](const DayInfo &day) {
        return day.Name == finalName;
    });

    if (it != days.end()) {
        return *it;
    } else {
        throw std::runtime_error("Day with the given name not found.");
    }
}


void printTable(std::vector<DayInfo> &resultInfos) {
    ft_table_t *table = ft_create_table();
    ft_set_border_style(table, FT_DOUBLE2_STYLE);
    size_t row = 0;

    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ++row;
    ft_set_cell_prop(table, 1, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ++row;
    ft_write_ln(table, "", "Self-test", "", "Part A", "", "Part B");
    ft_write_ln(table, "Day", "A", "B", "Time (uS)", "Code", "Time (uS)", "Code");
    for (auto &day: resultInfos) {
        if (day.hasRun) {
            ft_write_ln(table, day.Name.c_str(), day.TestAPass ? "Pass" : "Fail", day.TestBPass ? "Pass" : "Fail",
                        std::to_string(day.executionTimeA).c_str(), day.codeA.c_str(),
                        std::to_string(day.executionTimeB).c_str(), day.codeB.c_str());
            ft_set_cell_prop(table, row, 1, FT_CPROP_CONT_FG_COLOR, day.TestAPass ? FT_COLOR_GREEN : FT_COLOR_RED);
            ft_set_cell_prop(table, row, 2, FT_CPROP_CONT_FG_COLOR, day.TestBPass ? FT_COLOR_GREEN : FT_COLOR_RED);
            ++row;

        }
    }

    /* Set cell span */
    ft_set_cell_span(table, 0, 1, 2);
    ft_set_cell_span(table, 0, 3, 2);
    ft_set_cell_span(table, 0, 5, 2);
    printf("%s\n", ft_to_string(table));
    ft_destroy_table(table);
}


int main(int argc, char *argv[]) {
    std::vector<DayInfo> days = createDays();
    if (argc < 2) {


        for (auto &day: days) {
            day.hasRun = true;
            DayExecutor executor(std::move(day.day));

            day.TestAPass = executor.executeTestPart1();
            day.TestBPass = executor.executeTestPart2();

            DayResult part1Result = executor.executePart1();
            day.executionTimeA = part1Result.part1ExecutionTime.count();
            day.codeA = part1Result.part1Result;


            DayResult part2Result = executor.executePart2();
            day.executionTimeB = part2Result.part2ExecutionTime.count();
            day.codeB = part2Result.part2Result;
        }
    } else {
        // Run a specific dayId if an argument is given
        auto &day = findDayByName(days, argv[2]);
        day.hasRun = true;

        std::cout << "Running Day " << (argv[2]) << "..." << std::endl;
        DayExecutor executor(std::move(day.day));

        day.TestAPass = executor.executeTestPart1();
        day.TestBPass = executor.executeTestPart2();

        DayResult part1Result = executor.executePart1();
        day.executionTimeA = part1Result.part1ExecutionTime.count();
        day.codeA = part1Result.part1Result;


        DayResult part2Result = executor.executePart2();
        day.executionTimeB = part2Result.part2ExecutionTime.count();
        day.codeB = part2Result.part2Result;

    }
    printTable(days);
    return 0;
}
