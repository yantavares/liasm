#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <program_file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cerr << "Could not open the file." << std::endl;
        return 1;
    }

    std::string line, instr, var;
    int ACC = 0;                                  // Accumulator
    std::unordered_map<std::string, int> memory;  // Simulated memory
    std::unordered_map<std::string, int> labels;  // Labels for jumps
    std::unordered_map<int, std::string> program; // Stores the program line by line

    // First pass: builds the label map and stores the lines of the program
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
        }

        else if (instr == "SPACE")
        {
            memory[label] = 0;
        }

        else if (instr == "STOP")
        {
            program[address] = instr;
            address++;
            while (iss >> instr)
            {
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

    // Second pass: executes the program
    int PC = 0;
    instr = "";
    while (instr != "STOP")
    {
        instr = program[PC];

        if (instr == "INPUT")
        {
            label = program[PC + 1];
            std::cout << "Enter a value for " << label << ": ";
            std::cin >> memory[label];
            PC += 2;
        }
        else if (instr == "LOAD")
        {
            label = program[PC + 1];
            ACC = memory[label];
            PC += 2;
        }
        else if (instr == "ADD")
        {
            label = program[PC + 1];
            ACC += memory[label];
            PC += 2;
        }
        else if (instr == "SUB")
        {
            label = program[PC + 1];
            ACC -= memory[label];
            PC += 2;
        }
        else if (instr == "MULT")
        {
            label = program[PC + 1];
            ACC *= memory[label];
            PC += 2;
        }
        else if (instr == "STORE")
        {
            label = program[PC + 1];
            memory[label] = ACC;
            PC += 2;
        }
        else if (instr == "OUTPUT")
        {
            label = program[PC + 1];
            std::cout << label << " = " << memory[label] << std::endl;
            PC += 2;
        }
        else if (instr == "STOP")
        {
            break;
        }
        else if (instr == "SPACE")
        {
            label = program[PC + 1];
            memory[label] = 0; // Initializes memory with 0
            PC++;
        }
        else if (instr == "CONST")
        {
            label = program[PC + 1];
            int value = stoi(program[PC + 2]);
            memory[label] = value;
            PC++;
        }
        else if (instr == "JUMPZ")
        {
            label = program[PC + 1];
            if (ACC == 0)
            {
                PC = labels[label];
            }
            else
                PC += 2;
        }
        else if (instr == "JUMPP")
        {
            label = program[PC + 1];
            if (ACC > 0)
            {
                PC = labels[label];
            }
            else
                PC += 2;
        }
        else if (instr == "JUMPN")
        {
            label = program[PC + 1];
            if (ACC < 0)
            {
                PC = labels[label];
            }
            else
                PC += 2;
        }
        else if (instr == "JUMP")
        {
            label = program[PC + 1];
            PC = labels[label];
        }
    }

    return 0;
}
