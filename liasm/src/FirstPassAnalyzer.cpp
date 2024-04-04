#include "FirstPassAnalyzer.hpp"

FirstPassAnalyzer::FirstPassAnalyzer(
    std::unordered_map<std::string, int> &memory,
    std::unordered_map<std::string, int> &labels,
    std::unordered_map<int, std::string> &program)
    : memory(memory), labels(labels), program(program)
{
}

int FirstPassAnalyzer::analyse(std::ifstream &file)
{
    std::string line, instr, var;
    std::string label;
    int address = 0;

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

void FirstPassAnalyzer::processInstruction(std::string &instr, std::istringstream &iss,
                                           std::string &label, int &address)
{
    std::string var;

    if (instr.back() == ':')
    {
        label = instr.substr(0, instr.size() - 1);

        labels[label] = address;

        if (!(iss >> instr))
        {
            return;
        }
    }

    if (instr == "CONST")
    {
        iss >> var;
        memory[label] = std::stoi(var);
        address++;
    }
    else if (instr == "SPACE")
    {
        memory[label] = 0;
        address++;
    }
    else if (instr == "STOP")
    {
        stopFlag = true;
    }

    // Record instruction and possibly additional operands
    program[address++] = instr;
    while (!stopFlag && iss >> instr)
    {
        if (instr[0] == ';')
        {
            break; // Comment detected, stop processing the line
        }
        program[address++] = instr;
    }
}

void FirstPassAnalyzer::printLabels()
{
    std::cout << "Label"
              << " ->  "
              << "Address" << std::endl;

    for (auto &kv : labels)
    {
        int spacesToAddLabel = 5 - kv.first.size(); // 5 is the size of the string "LABEL"
        std::string spacesLabel(spacesToAddLabel, ' ');

        std::cout << kv.first << spacesLabel << " ->  " << kv.second << std::endl;
    }

    std::cout << std::endl;
}
