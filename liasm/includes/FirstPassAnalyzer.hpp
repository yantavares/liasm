#ifndef FIRSTPASSANALYZER_HPP
#define FIRSTPASSANALYZER_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

class FirstPassAnalyzer
{
public:
    FirstPassAnalyzer(
        std::unordered_map<std::string, int> &memory,
        std::unordered_map<std::string, int> &labels,
        std::unordered_map<int, std::string> &program);

    int analyse(std::ifstream &file);
    void printLabels();

private:
    std::unordered_map<std::string, int> &memory;
    std::unordered_map<std::string, int> &labels;
    std::unordered_map<int, std::string> &program;

    bool stopFlag = false;

    void processInstruction(std::string &instr, std::istringstream &iss,
                            std::string &label, int &address);
};

#endif // FIRSTPASSANALYZER_HPP
