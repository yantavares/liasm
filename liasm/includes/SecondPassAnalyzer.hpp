#ifndef SECONDPASSANALYZER_HPP
#define SECONDPASSANALYZER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class SecondPassAnalyzer
{
public:
    SecondPassAnalyzer(std::vector<u_int16_t> &RAM,
                       std::vector<u_int16_t> &ROM,
                       std::unordered_map<std::string, u_int16_t> &labels);

    int analyse(std::ifstream &file);

private:
    std::vector<u_int16_t> &RAM;
    std::vector<u_int16_t> &ROM;
    std::unordered_map<std::string, u_int16_t> &labels;

    bool stopFlag = false;

    void processInstruction(std::string &instr, std::istringstream &iss,
                            std::string &label, u_int16_t &address);

    u_int16_t getOpcode(std::string &instr);

    std::unordered_map<std::string, u_int16_t> opcodes{
        {"STOP", 0x00},
        {"INPUT", 0x01},
        {"LOAD", 0x02},
        {"ADD", 0x03},
        {"SUB", 0x04},
        {"MULT", 0x05},
        {"STORE", 0x06},
        {"OUTPUT", 0x07},
        {"JUMPZ", 0x08},
        {"JUMPP", 0x09},
        {"JUMPN", 0x0A},
        {"JUMP", 0x0B},
    };
};

#endif // SECONDPASSANALYZER_HPP