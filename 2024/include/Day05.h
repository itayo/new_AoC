#ifndef DAY05_H
#define DAY05_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>


class Day05 : public DayBase {
public:
    Day05() {
        m_rawDataA = aoc.ReadFile("Data/input05A.txt");
        m_rawDataB = aoc.ReadFile("Data/input05B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input05A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input05B.txt");
        PrepareData();
    }


    std::string part1() override;

    std::string part2() override;

    bool testPart1() override;

    bool testPart2() override;

private:

    class Internal {
    public:
        struct PrintOrder {
            PrintOrder();
            PrintOrder(std::vector<int32_t> vec) : pages(std::move(vec)) {}
            PrintOrder(bool good, std::vector<int32_t> vec) : isGood(good),pages(std::move(vec)){};
            bool isGood=true;
            std::vector<int32_t> pages;
        };

        typedef std::unordered_map<int32_t,std::vector<int32_t>> RuleMap;
        typedef std::vector<PrintOrder> PagesOrders;

        void none(){};


    };
    struct Data {

        struct {};
        Internal::RuleMap ShouldBeBeforeRule;
        Internal::RuleMap ShouldBeAfterRule;
        Internal::PagesOrders PageOrders;
        std::vector<std::pair<int32_t,int32_t>> Rules;


    };
    const uint32_t ExpectedTestA = 143;
    const uint32_t ExpectedTestB = 123;

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
    void SortGoodOrBad(Data &data);
    bool CheckIfGood(std::vector<int32_t> pages, Data data);
    std::vector<Internal::PrintOrder> GetPrints(Data &data, bool status) {
        auto &pageOrders = data.PageOrders;
        std::vector<Internal::PrintOrder> prints;
        std::copy_if(pageOrders.begin(), pageOrders.end(), std::back_inserter(prints),
                     [&status](const Internal::PrintOrder &order) {
                         return order.isGood == status;
                     });
        return prints;
    }
};


#endif // DAY05_H
