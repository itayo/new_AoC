#ifndef DAY04_H
#define DAY04_H

#include "DayBase.h"
#include <string>
#include <AoC/aoc.h>
#include <openssl/md5.h>
#include <iomanip>


class Day04 : public DayBase {
public:
    Day04() {
        m_rawDataA = aoc.ReadFile("Data/input04A.txt");
        m_rawDataB = aoc.ReadFile("Data/input04B.txt");
        m_rawDataTestA = aoc.ReadFile("TestData/input04A.txt");
        m_rawDataTestB = aoc.ReadFile("TestData/input04B.txt");
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
        static void md5(const std::string &str, std::string &md5String){
            unsigned char hash[MD5_DIGEST_LENGTH];

            MD5_CTX md5;
            MD5_Init(&md5);
            MD5_Update(&md5, str.c_str(), str.size());
            MD5_Final(hash, &md5);

            std::stringstream ss;

            for(int i = 0; i < MD5_DIGEST_LENGTH; i++){
                ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>( hash[i] );
            }
            md5String = ss.str();
        }
    };
    struct Data {
        std::string prefix;

    };
    const uint32_t ExpectedTestA = 609043;
    const uint32_t ExpectedTestB = 6742839;

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


#endif // DAY04_H
