#include "firstPass.hpp"

int firstPass(std::ifstream &file,
              std::unordered_map<std::string, int> &memory,
              std::unordered_map<std::string, int> &labels,
              std::unordered_map<int, std::string> &program)

{
    // First pass: builds the label map and stores the lines of the program
    std::string line, instr, var;

    std::string label;
    int address = 0;
    bool stopFlag = false;
    while (getline(file, line))
    {
        std::istringstream iss(line);
        if (!(iss >> instr))
            continue; // Empty line or no instruction

        // Checks if the instruction is actually a label
        if (instr.back() == ':')
        {
            label = instr.substr(0, instr.size() - 1);

            labels[label] = address;

            if (!(iss >> instr))
                continue; // Empty line or no instruction
        }

        if (instr == "CONST")
        {
            iss >> var;
            memory[label] = stoi(var);
            address++;
        }

        else if (instr == "SPACE")
        {
            memory[label] = 0;
            address++;
        }

        else if (instr == "STOP")
        {
            program[address] = instr;
            address++;
            while (iss >> instr)
            {
                if (instr[0] == ';')
                    break;
                program[address] = instr;
                address++;
            }

            stopFlag = true;
        }

        if (!stopFlag)
        {
            program[address] = instr;
            address++;
            while (iss >> instr)
            {
                if (instr[0] == ';')
                    break;
                program[address] = instr;
                address++;
            }
        }
    }

    file.close();

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
    return 0;
}
