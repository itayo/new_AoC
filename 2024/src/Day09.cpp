#include "Day09.h"
#include <iostream>

void Day09::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    for (auto &chr: raw[0]) {
        formatted.fs.push_back(chr - '0');
    }
}

uint64_t Day09::Execute1(Data data) {
    auto isFile = [](int x) { return x >= 0; };
    uint64_t result = 0;
    auto &raw = data.raw;
    int fileID = 0;
    std::vector<int> disk;
    for (size_t i = 0; i < data.fs.size(); ++i) {
        int size = data.fs[i];
        if (i % 2 == 1) {
            disk.insert(disk.end(), size, -1);
        } else {
            disk.insert(disk.end(), size, fileID++);

        }
    }

    size_t start = 0;
    size_t end = disk.size() - 1;
    while (start < end) {

        while (start < disk.size() && disk[start] >= 0) ++start;
        while (end > 0 && disk[end] < 0) --end;
        if (start < end) {
            std::swap(disk[start], disk[end]);
            ++start;
            --end;
        }

    }
    for (size_t i = 0; i < disk.size() && disk[i] != -1; ++i) {
        result += i * disk[i];
    }

    return result;

}

uint64_t Day09::Execute2(Data data) {
    uint64_t result = 0;
    int fileID = 0;
    std::vector<Internal::fs> fs;

    auto rit = fs.rbegin();
    auto fit = fs.begin();
    auto sit = fs.begin();
    auto rPosId = [&fs, &rit]() { return fs.size() - 1 - std::distance(fs.rbegin(), rit); };
    auto fPosId = [&fs, &fit]() { return std::distance(fs.begin(), fit); };
    auto sPosId = [&fs, &sit]() { return std::distance(fs.begin(), sit); };
    auto pos = 0;
    for (size_t i = 0; i < data.fs.size(); ++i) {
        int size = data.fs[i];
        Internal::fs f;
        f.size = size;
        f.pos = pos;
        if (i % 2 == 1) {
            f.id = -1;
            fs.emplace_back(f);
        } else {
            f.id = fileID;
            ++fileID;
            fs.emplace_back(f);
        }
        pos += size;
    }
    rit = fs.rbegin();
    fit = fs.begin();


    while (rit != fs.rend()) {
        while (rit->id == -1) ++rit;
        sit = std::find_if(fs.begin(), fs.end(),
                           [&rit](Internal::fs &fs) { return fs.id == -1 && fs.size >= rit->size; });
        if (sPosId() < rPosId()) {
            if (sit->size > rit->size) {
                Internal::fs ns{-1, sit->size - rit->size, sit->pos + rit->size};
                sit->size = rit->size;
                fs.insert(sit + 1, ns);
                rit--;
            }
            std::swap(sit->id,rit->id);
        }
        ++rit;
        fit=fs.begin();
    }
    for(auto f:fs) {
        if(f.id==-1) continue;
        for(int x=0;x< f.size;++x) result += ((f.pos+x) * f.id);
    }

return result;

}

bool Day09::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day09::part1() {
    auto result = Execute1(m_DataA);
    return std::to_string(result);
}


bool Day09::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day09::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
