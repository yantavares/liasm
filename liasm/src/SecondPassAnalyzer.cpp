#include "SecondPassAnalyzer.hpp"

SecondPassAnalyzer::SecondPassAnalyzer(

    std::unordered_map<std::string, u_int16_t> &labels)
    : labels(labels), elementSize(16) // 16 bits per element
{
    RAM = new std::fstream("./RAM.txt", std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
    ROM = new std::fstream("./ROM.txt", std::ios::in | std::ios::out | std::ios::binary | std::ios::ate);
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
    }
}

u_int16_t SecondPassAnalyzer::getOpcode(std::string &inst)
{
    return opcodes[inst];
}

void SecondPassAnalyzer::writeValueToFile(u_int16_t type, u_int16_t index, u_int16_t value)
{
    // Convert the value to a binary string
    std::string binaryString = std::bitset<16>(value).to_string();

    // Calculate the position in the file.
    // Note: This calculation assumes each line in the file is 16 characters long plus a newline character.
    std::streampos pos = index * (elementSize + 1); // +1 for the newline character

    switch (type)
    {
    case 0:
        RAM->seekp(pos);
        *RAM << binaryString << std::endl; // Write the binary string with a newline
        break;

    case 1:
        ROM->seekp(pos);
        *ROM << binaryString << std::endl; // Write the binary string with a newline
        break;
    }
}
