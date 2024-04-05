#ifndef SECONDPASSANALYZER_HPP
#define SECONDPASSANALYZER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <bitset>
#include <memory>

class SecondPassAnalyzer
{
public:
    SecondPassAnalyzer(
        std::unordered_map<std::string, u_int16_t> &labels);

    int analyse(std::ifstream &file);

private:
    std::unordered_map<std::string, u_int16_t> &labels;

    bool stopFlag = false;

    void parseInstruction(std::string &instr, std::istringstream &iss,
                          std::string &label, u_int16_t &address);

    u_int16_t getOpcode(std::string &instr);

    void writeValueToFile(u_int16_t type, u_int16_t index, u_int16_t value);

    std::unordered_map<std::string, u_int16_t> opcodes{
        {"ADD", 0x01},
        {"SUB", 0x02},
        {"MUL", 0x03},
        {"DIV", 0x04},
        {"JMP", 0x05},
        {"JMPN", 0x06},
        {"JMPP", 0x07},
        {"JMPZ", 0x08},
        {"COPY", 0x09},
        {"LOAD", 0x0A},
        {"STORE", 0x0B},
        {"INPUT", 0x0C},
        {"OUTPUT", 0x0D},
        {"STOP", 0x0E}};

    u_int16_t elementSize;

protected:
    std::unique_ptr<std::fstream> RAM;
    std::unique_ptr<std::fstream> ROM;
};

#endif // SECONDPASSANALYZER_HPP