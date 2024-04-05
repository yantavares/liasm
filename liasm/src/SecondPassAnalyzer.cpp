#include "SecondPassAnalyzer.hpp"

SecondPassAnalyzer::SecondPassAnalyzer(

    std::unordered_map<std::string, u_int16_t> &labels)
    : labels(labels)
{
    const std::streamsize elementSize = sizeof(uint16_t);
    this->elementSize = elementSize;

    RAM = new std::fstream("./RAM.txt", std::ios::out | std::ios::binary | std::ios::ate);
    this->RAM = RAM;

    ROM = new std::fstream("./ROM.txt", std::ios::out | std::ios::binary | std::ios::ate);
    this->ROM = ROM;
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

        writeValueToFile(0, labels[label], value); // Write to RAM
        address++;
    }
    else if (instr == "SPACE")
    {
        writeValueToFile(0, labels[label], 0); // Write to RAM
        address++;
    }
    else if (instr == "STOP")
    {
        stopFlag = true;
    }

    if (labels.find(instr) != labels.end())
    {
        writeValueToFile(1, address, labels[instr]); // Write to ROM
    }
    else
    {
        writeValueToFile(1, address, getOpcode(instr)); // Write to ROM
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
            writeValueToFile(1, address, labels[instr]); // Write to ROM
        }
        else
        {
            writeValueToFile(1, address, getOpcode(instr)); // Write to ROM
        }
        address++;
        iss >> instr;
    }
}

u_int16_t SecondPassAnalyzer::getOpcode(std::string &inst)
{
    return opcodes[inst];
}

void SecondPassAnalyzer::writeValueToFile(u_int16_t type, u_int16_t index, u_int16_t value)
{
    switch (type)
    {
    case 0:
        std::streampos pos = index * elementSize;
        RAM->seekp(pos);
        RAM->write(reinterpret_cast<const char *>(&value), elementSize);
        break;

    case 1:
        std::streampos pos = index * elementSize;
        ROM->seekp(pos);
        ROM->write(reinterpret_cast<const char *>(&value), elementSize);
        break;
    }
}
