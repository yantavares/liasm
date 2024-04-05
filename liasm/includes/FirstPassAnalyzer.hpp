#ifndef FIRSTPASSANALYZER_HPP
#define FIRSTPASSANALYZER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

class FirstPassAnalyzer
{
public:
    FirstPassAnalyzer(std::unordered_map<std::string, u_int16_t> &labels);

    int analyse(std::ifstream &file);
    void printLabels();
    bool isLabelValid(std::string &label, bool checkExists = true);
    bool isInstrValid(std::string &instr);

private:
    std::unordered_map<std::string, u_int16_t> &labels;

    bool stopFlag = false;

    void scanIntruction(std::string &instr, std::istringstream &iss,
                        std::string &label, u_int16_t &address);

    std::vector<std::string> reservedWords{
        "CONST", "SPACE", "STOP", "INPUT", "LOAD",
        "ADD", "SUB", "MULT", "STORE", "OUTPUT", "JUMPZ",
        "JUMPP", "JUMPN", "JUMP"};
};

#endif // FIRSTPASSANALYZER_HPP
