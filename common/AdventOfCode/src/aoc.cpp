#include <string>
#include <vector>
#include <iterator>
#include <fstream>
#include <sstream>
#include <regex>
#include "AoC/aoc.h"

namespace AoC {

    AoCInput AoC::ReadFile(std::string file_path) {
        std::ifstream file(file_path);
        std::string line;
        std::vector<std::string> v;
        while (std::getline(file, line)) {
            v.push_back(line);
        }
        return v;
    }

    AoCInput AoC::StringSplit(const std::string &line, char delimiter) {
        std::string part;
        std::vector<std::string> result;
        std::stringstream stream(line);
        while (std::getline(stream, part, delimiter)) {
            result.push_back(part);
        }
        return result;
    }

    void AoC::StringReplace(std::string &line, std::vector<tStringToReplace> replacers) {
        for (tStringToReplace replacer: replacers) {
            size_t pos = 0;
            while ((pos = line.find(replacer.what)) != std::string::npos) {
                line.replace(pos, replacer.what.length(), replacer.withWhat);
            }
        }

    }

    void AoC::StringReplace(std::vector<std::string> &lines, std::vector<tStringToReplace> replacers) {
        for (size_t i = 0; i < lines.size(); i++) {
            StringReplace(lines[i], replacers);
        }

    }

    std::vector<int> AoC::GetAllIntegersS32(std::string line) {
        std::regex rx("(\\d+)");
        std::smatch match;
        std::vector<int> results;
        while (regex_search(line, match, rx)) {
            size_t start = line.find(match[1].str());
            int value = std::stoi(match[1].str());
            line = match.suffix().str();
            results.push_back(value);

        }
        return results;
    }

    AoCInput AoC::ExtractMatches(std::regex rx, std::string line) {
        std::smatch match;
        std::vector<std::string> results;
        while (regex_search(line, match, rx)) {
            for (int i = 1; i < match.size(); ++i) {
                results.emplace_back(match[i].str());
            }
            line = match.suffix().str();

        }
        return results;
    }

    std::vector<uint64_t> AoC::GetAllIntegersU64(std::string line) {
        std::regex rx("(\\d+)");
        std::smatch match;
        std::vector<uint64_t> results;
        while (regex_search(line, match, rx)) {
            size_t start = line.find(match[1].str());
            unsigned long long value = std::stoull(match[1].str());
            line = match.suffix().str();
            results.push_back(value);

        }
        return results;
    }

    bool AoC::StringEndsWith(std::string const &value, std::string const &ending) {
        if (ending.size() > value.size()) return false;
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }
}

