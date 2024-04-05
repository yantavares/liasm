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

    address++;

    if (instr == "CONST")
    {
        if (!(iss >> var) || !std::all_of(var.begin(), var.end(), ::isdigit))
        {
            throw std::runtime_error("CONST instruction must have a value.");
            return;
        }

        address++;
    }
    else if (instr == "SPACE")
    {
        if (iss >> var && var[0] != ';')
        {
            throw std::runtime_error("SPACE instruction must not have a value.");
            return;
        }
        address++;
    }
    else if (instr == "STOP")
    {
        if (iss >> var && var[0] != ';')
        {
            throw std::runtime_error("STOP instruction must not have a value.");
            return;
        }
        stopFlag = true;
    }
    else
    {
        if (!(iss >> var))
        {
            throw std::runtime_error("Instruction " + instr + " must have a value.");
            return;
        }

        if (!isLabelValid(var, false))
        {
            return;
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

bool FirstPassAnalyzer::isLabelValid(std::string &label, bool checkExits)
{
    if (checkExits)
    {
        if (labels.find(label) != labels.end())
        {
            throw std::runtime_error("Label " + label + " already exists.");
            return false;
        }
    }

    if (!isalpha(label[0]))
    {
        throw std::runtime_error("Label " + label + " must start with a letter.");
        return false;
    }

    if (std::find(reservedWords.begin(), reservedWords.end(), label) != reservedWords.end())
    {
        throw std::runtime_error("Label " + label + " is a reserved word.");
        return false;
    }

    return true;
}

bool FirstPassAnalyzer::isInstrValid(std::string &instr)
{
    if (std::find(reservedWords.begin(), reservedWords.end(), instr) == reservedWords.end())
    {
        throw std::runtime_error("Instruction " + instr + " is not valid.");
        return false;
    }

    return true;
}