#include "FirstPassAnalyzer.hpp"

FirstPassAnalyzer::FirstPassAnalyzer(
    std::unordered_map<std::string, u_int16_t> &labels)
    : labels(labels)
{
}

int FirstPassAnalyzer::analyse(std::ifstream &file)
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

        scanIntruction(instr, iss, label, address);
    }

    file.close();

    return 0;
}

void FirstPassAnalyzer::scanIntruction(std::string &instr, std::istringstream &iss,
                                       std::string &label, u_int16_t &address)
{
    std::string var;

    if (instr.back() == ':')
    {
        label = instr.substr(0, instr.size() - 1);

        if (!isLabelValid(label))
        {
            return;
        }

        labels[label] = address;

        if (!(iss >> instr))
        {
            return;
        }
    }

    if (!isInstrValid(instr))
    {
        return;
    }

    if (instr == "CONST")
    {
        address++;
    }
    else if (instr == "SPACE")
    {
        address++;
    }
    else if (instr == "STOP")
    {
        stopFlag = true;
    }

    address++;
    while (!stopFlag && iss >> instr)
    {
        if (instr[0] == ';')
        {
            break; // Comment detected, stop processing the line
        }
        address++;
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

bool FirstPassAnalyzer::isLabelValid(std::string &label)
{
    if (labels.find(label) != labels.end())
    {
        std::cerr << "Label " << label << " already exists." << std::endl;
        return false;
    }

    if (!isalpha(label[0]))
    {
        std::cerr << "Label " << label << " must start with a letter." << std::endl;
        return false;
    }

    if (std::find(reservedWords.begin(), reservedWords.end(), label) != reservedWords.end())
    {
        std::cerr << "Label " << label << " is a reserved word." << std::endl;
        return false;
    }

    return true;
}

bool FirstPassAnalyzer::isInstrValid(std::string &instr)
{
    if (std::find(reservedWords.begin(), reservedWords.end(), instr) == reservedWords.end())
    {
        std::cerr << "Instruction " << instr << " is not valid." << std::endl;
    }

    return true;
}