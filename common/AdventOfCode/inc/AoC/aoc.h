#ifndef ADVENTOFCODE_LIB_H
#define ADVENTOFCODE_LIB_H
#include <vector>
#include <string>
#include <regex>
#include "Assertion.h"
namespace AoC {
    using  AoCInput= std::vector<std::string>;
#define UNUSED(x)  (void)((x))
    struct tStringToReplace {
        tStringToReplace() { }
        tStringToReplace(std::string a, std::string b)
                :what(a), withWhat(b) { }

        std::string what;
        std::string withWhat;
    };
    class AoC {
    public:
        std::vector<std::string> ReadFile(std::string file);
        template<typename tType>
        void Unused(tType type) { UNUSED(type);}

        std::vector<std::string> StringSplit(const std::string& line, char delimiter);
        void StringReplace(std::string& string, std::vector<tStringToReplace> replacers);
        void StringReplace(std::vector<std::string>& strings, std::vector<tStringToReplace> replacers);
        std::vector<int> GetAllIntegersS32(std::string line);
        std::vector<uint64_t> GetAllIntegersU64(std::string line);
        std::vector<std::string> ExtractMatches(std::regex rx, std::string line);
        bool StringEndsWith(std::string const& value, std::string const& ending);
        uint64_t ABS_U64(uint64_t a, uint64_t b) {
            return std::max(a, b) - std::min(a, b);
        }
    };
}
#endif
