#include "Day23.h"
#include "AoC/GenericHasher.h"
#include <set>
#include <AoC/LinkedList.h>

void Day23::PrepareData(AoC::AoCInput &raw, Data &formatted) {
    formatted.Raw = raw;
}

struct VectorHash {
    std::size_t operator()(const std::vector<std::string> &vec) const {
        std::size_t seed = vec.size();
        for (const auto &str: vec) {
            for (char ch: str) {
                seed ^= std::hash<char>()(ch) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
        }
        return seed;
    }
};

std::pair<Day23::NetworkMap, Day23::NetworkNodes> Day23::parseInput(const AoC::AoCInput &puzzleInput) {
    NetworkMap networkMap;
    NetworkNodes nodes;
    std::regex connectionPattern(R"((\w+)-(\w+))");
    for (auto &conn: puzzleInput) {
        auto c = aoc.StringSplit(conn, '-');
        networkMap[c[0]].insert(c[1]);
        networkMap[c[1]].insert(c[0]);
        nodes.emplace(c[0]);
        nodes.emplace(c[1]);
    }
    std::pair<Day23::NetworkMap, std::unordered_set<std::string>> res;
    res.first = std::move(networkMap);
    res.second = std::move(nodes);
    return res;
}

std::unordered_set<std::vector<std::string>, VectorHash> GetTriConns(Day23::NetworkMap &networkMap) {
    std::vector<std::string> candidates;
    std::unordered_set<std::vector<std::string>, VectorHash> triConns;
    for (const auto &computers: networkMap) {
        if (!computers.first.empty() && computers.first[0] == 't') {
            candidates.push_back(computers.first);
        }
    }

    for (const auto &t: candidates) {
        for (const auto &a: networkMap[t]) {
            for (const auto &b: networkMap[a]) {
                if (networkMap[t].find(b) != networkMap[t].end()) {
                    AoC::AoCInput conns = {t, a, b};
                    std::sort(conns.begin(), conns.end());
                    triConns.insert(conns);
                }
            }
        }
    }
    return std::move(triConns);
}

uint64_t Day23::Execute1(Data &data) {

    auto [networkMap, networkNodes] = parseInput(data.Raw);


    return GetTriConns(networkMap).size();
}

std::string join(const std::vector<std::string> &vec, const std::string &delimiter) {
    std::ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
        oss << vec[i];
        if (i != vec.size() - 1) {
            oss << delimiter;
        }
    }
    return oss.str();
}

void bronKerbosch(const Day23::NetworkMap& networkMap,
                  std::unordered_set<std::string>& R,
                  std::unordered_set<std::string>& P,
                  std::unordered_set<std::string>& X,
                  std::vector<std::unordered_set<std::string>>& cliques) {
    if (P.empty() && X.empty()) {
        cliques.push_back(R);
        return;
    }


    std::unordered_set<std::string> P_copy = P;
    for (const auto& v : P_copy) {

        std::unordered_set<std::string> newR = R;
        newR.insert(v);

        std::unordered_set<std::string> newP;
        std::unordered_set<std::string> newX;


        for (const auto& neighbor : networkMap.at(v)) {
            if (P.find(neighbor) != P.end()) {
                newP.insert(neighbor);
            }
            if (X.find(neighbor) != X.end()) {
                newX.insert(neighbor);
            }
        }


        bronKerbosch(networkMap, newR, newP, newX, cliques);


        P.erase(v);
        X.insert(v);
    }
}

std::string findLargestClique(const Day23::NetworkMap& networkMap) {
    std::unordered_set<std::string> R, P, X;
    std::vector<std::unordered_set<std::string>> cliques;


    for (const auto& pair : networkMap) {
        P.insert(pair.first);
    }


    bronKerbosch(networkMap, R, P, X, cliques);

    std::unordered_set<std::string> largestClique;
    for (const auto& clique : cliques) {
        if (clique.size() > largestClique.size()) {
            largestClique = clique;
        }
    }


    std::vector<std::string> sortedClique(largestClique.begin(), largestClique.end());
    std::sort(sortedClique.begin(), sortedClique.end());
    return join(sortedClique, ",");
}


std::string Day23::Execute2(Data &data) {
    auto [networkMap, networkNodes] = parseInput(data.Raw);
    std::cout << "Network Map:\n";
    for (const auto& pair : networkMap) {
        std::cout << pair.first << ": ";
        for (const auto& neighbor : pair.second) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
    std::string password = findLargestClique(networkMap);
    return password;
}

bool Day23::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day23::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}


bool Day23::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day23::part2() {
    auto result = Execute2(m_DataB);
    return result;
}
