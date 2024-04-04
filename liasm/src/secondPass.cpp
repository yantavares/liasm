#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int secondPass(int &ACC,
               int &PC,
               std::unordered_map<std::string, int> &memory,
               std::unordered_map<std::string, int> &labels,
               std::unordered_map<int, std::string> &program)
{
    std::string label = "", var = "", instr = "";

    // Second pass: executes the program
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
        else
        {
            std::cerr << "Invalid instruction: " << instr << " at address " << PC << std::endl;
            return 1;
        }
    }
    return 0;
}