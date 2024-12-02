#include "DayBase.h"
#include "DayExecutor.h"
#include "TestData.h"
#include <iostream>
#include <memory>
#include <vector>
#include "fort.h"
#include "Day01.h"
#include "Day02.h"
//DayHeader

struct DayInfo {
    std::unique_ptr<DayBase> day;
    std::string Name;
    bool hasRun = false;
    bool TestAPass = false;
    bool TestBPass = false;
    uint64_t executionTimeA;
    std::string codeA;
    uint64_t executionTimeB;
    std::string codeB;

};

std::vector<DayInfo> createDays() {
    std::vector<DayInfo> days;
    days.push_back({std::make_unique<Day01>(), "01"});
    days.push_back({std::make_unique<Day02>(), "02"});
    //dayCreator
    return days;
}


void printTable(std::vector<DayInfo> &resultInfos) {
    ft_table_t *table = ft_create_table();
    ft_set_border_style(table, FT_DOUBLE2_STYLE);

    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_set_cell_prop(table, 1, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_write_ln(table, "", "Self-test", "", "Part A", "", "Part B");
    ft_write_ln(table, "Day", "A", "B", "Time (uS)", "Code", "Time (uS)", "Code");
    for (auto &day: resultInfos) {

        ft_write_ln(table, day.Name.c_str(), day.TestAPass ? "Pass" : "Fail", day.TestBPass ? "Pass" : "Fail",
                    std::to_string(day.executionTimeA).c_str(), day.codeA.c_str(),
                    std::to_string(day.executionTimeB).c_str(), day.codeB.c_str());
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


        for (size_t i = 0; i < days.size(); ++i) {
            auto &day = days[i];
            day.hasRun = true;
            DayExecutor executor(std::move(day.day));

            // Execute and print test results for Part 1
            day.TestAPass = executor.executeTestPart1();
            day.TestBPass = executor.executeTestPart2();



            // Execute and display results for Part 1 and Part 2
            DayResult part1Result = executor.executePart1();
            day.executionTimeA = part1Result.part1ExecutionTime.count();
            day.codeA = part1Result.part1Result;


            DayResult part2Result = executor.executePart2();
            day.executionTimeB = part2Result.part2ExecutionTime.count();
            day.codeB = part2Result.part2Result;
        }
    } else {
        // Run a specific dayId if an argument is given
        int dayId = std::stoi(argv[1]) - 1; // Convert to 0-based index

        if (dayId < 0 || dayId >= days.size()) {
            std::cerr << "Day " << (dayId + 1) << " not implemented or invalid" << std::endl;
            return 1;
        }
        auto &day = days[dayId];
        day.hasRun = true;

        std::cout << "Running Day " << (dayId + 1) << "..." << std::endl;
        DayExecutor executor(std::move(days[dayId].day));
        // Execute and print test results for Part 1
        day.TestAPass = executor.executeTestPart1();
        day.TestAPass = executor.executeTestPart2();



        // Execute and display results for Part 1 and Part 2
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