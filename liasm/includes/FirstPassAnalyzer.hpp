#ifndef FIRSTPASSANALYZER_HPP
#define FIRSTPASSANALYZER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class FirstPassAnalyzer
{
public:
    FirstPassAnalyzer(
        std::vector<uint16_t> &RAM,
        std::vector<std::string> &ROM,
        std::unordered_map<std::string, u_int16_t> &labels);

    int analyse(std::ifstream &file);
    void printLabels();

private:
    std::vector<uint16_t> &RAM;
    std::vector<std::string> &ROM;
    std::unordered_map<std::string, u_int16_t> &labels;

    bool stopFlag = false;

    void processInstruction(std::string &instr, std::istringstream &iss,
                            std::string &label, u_int16_t &address);
};

#endif // FIRSTPASSANALYZER_HPP
