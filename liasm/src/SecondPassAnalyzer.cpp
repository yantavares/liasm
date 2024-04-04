#include "SecondPassAnalyzer.hpp"

SecondPassAnalyzer::SecondPassAnalyzer(
    std::vector<uint16_t> &RAM,
    std::vector<uint16_t> &ROM,
    std::unordered_map<std::string, u_int16_t> &labels)
    : RAM(RAM), ROM(ROM), labels(labels)
{
}

int SecondPassAnalyzer::analyse(std::ifstream &file)
{

    std::string line, instr, var;
    std::string label;
    u_int16_t address = 0;

    while (getline(file, line))
    {
        std::istringstream iss(line);

        if (!(iss >> instr))
        {
            continue; // Empty line or no instruction
        }

        processInstruction(instr, iss, label, address);
    }

    file.close();

    return 0;
}

void SecondPassAnalyzer::processInstruction(std::string &instr, std::istringstream &iss,
                                            std::string &label, u_int16_t &address)
{

    if (instr.back() == ':')
    {
        label = instr.substr(0, instr.size() - 1);

        if (!(iss >> instr))
        {
            return;
        }
    }

    if (instr == "CONST")
    {
        u_int16_t value;
        iss >> value;

        RAM[labels[label]] = value;
        address++;
    }
    else if (instr == "SPACE")
    {
        RAM[labels[label]] = 0;
        address++;
    }
    else if (instr == "STOP")
    {
        stopFlag = true;
    }

    if (labels.find(instr) != labels.end())
    {
        ROM[address] = labels[instr];
    }
    else
    {
        ROM[address] = getOpcode(instr);
    }

    address++;

    while (!stopFlag && iss >> instr)
    {
        if (instr[0] == ';')
        {
            break; // Comment detected, stop processing the line
        }

        if (labels.find(instr) != labels.end())
        {
            ROM[address] = labels[instr];
        }
        else
        {
            ROM[address] = getOpcode(instr);
        }
        address++;
        iss >> instr;
    }
}

u_int16_t SecondPassAnalyzer::getOpcode(std::string &inst)
{
    return opcodes[inst];
}