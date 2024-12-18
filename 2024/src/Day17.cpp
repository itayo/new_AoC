#include "Day17.h"
#include <iostream>
#include <deque>

void Day17::PrepareData(std::vector<std::string> &raw, Data &formatted) {
    if (raw.size() != 5) throw std::runtime_error("input is bad");
    auto regA = aoc.GetAllIntegersU64(raw[0]);
    auto commands = aoc.GetAllIntegersS32(raw[4]);
    formatted.registers[0] = regA[0];
    std::copy(commands.begin(), commands.end(), std::back_inserter(formatted.opcodes));
}

std::vector<uint64_t> Day17::run(Data &data) {
    uint64_t ProgramCounter = 0;
    std::vector<uint64_t> out;
    auto &regA = data.registers[0];
    auto &regB = data.registers[1]=0;
    auto &regC = data.registers[2]=0;
    while (ProgramCounter < data.opcodes.size()) {

        uint64_t opcode = data.opcodes[ProgramCounter];
        uint64_t operand = data.opcodes[ProgramCounter + 1];
        ProgramCounter += 2;

        if (opcode != 3 && opcode != 1) {
            switch (operand) {
                case 4:
                    operand = regA;
                    break;
                case 5:
                    operand = regB;
                    break;
                case 6:
                    operand = regC;
                    break;
                default:
                    break;
            }
        }
        switch (opcode) {
            case 0:
                regA = regA >> operand;
                break;
            case 1:
                regB ^= operand;
                break;
            case 2:
                regB = operand & 0x7;
                break;
            case 3:
                if (regA != 0) ProgramCounter = operand;
                break;
            case 4:
                regB ^= regC;
                break;
            case 5:
                out.push_back(operand & 0x7);
                break;
            case 6:
                regB = regA >> operand;
                break;
            case 7:
                regC = regA >> operand;
                break;
            default:
                throw std::runtime_error("wierd opcode :" + std::to_string(opcode));
        }

    }
    return out;
}


std::string Day17::Execute1(Data &data) {


    std::string result;
    auto out = run(data);
    for(const auto &num: out){
        result += std::to_string(num);
        result += ",";
    }
    if (!result.empty()) result.pop_back();
    return result;
}

uint64_t Day17::dive(const std::vector<int> &goal,Data &data, uint64_t a, int depth) {
    if (depth == goal.size()) {
        return a;
    }
    for (int i = 0; i < 8; ++i) {
        uint64_t next=(a * 8) + i;
        data.registers[0]=next;
        auto output = run(data);
        if (!output.empty() && output[0] == goal[depth]) {
            uint64_t result = dive(goal,  data, next, depth + 1);
            if (result != 0) {
                return result;
            }
        }
    }
    return 0;
}

uint64_t Day17::Execute2(Data &data) {
    std::vector<int> goal(data.opcodes.rbegin(), data.opcodes.rend());
    data.registers[0]=0;
    auto result=dive(goal,data);
    data.registers[0]=result;
    auto dat =run(data);


    return  result;
}

bool Day17::testPart1() {
    auto result = Execute1(m_DataTestA);
    return ExpectedTestA == result;
}

std::string Day17::part1() {
    auto result = Execute1(m_DataA);
    return result;
}


bool Day17::testPart2() {
    auto result = Execute2(m_DataTestB);
    return ExpectedTestB == result;
}

std::string Day17::part2() {
    auto result = Execute2(m_DataB);
    return std::to_string(result);
}
