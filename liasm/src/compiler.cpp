#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "firstPass.hpp"
#include "secondPass.hpp"

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

    int ACC = 0, PC = 0;                          // Accumulator
    std::unordered_map<std::string, int> memory;  // Simulated memory
    std::unordered_map<std::string, int> labels;  // Labels for jumps
    std::unordered_map<int, std::string> program; // Stores the program line by line

    // First pass: builds the label map and stores the lines of the program
    firstPass(file, memory, labels, program);

    // Second pass: executes the program
    secondPass(ACC, PC, memory, labels, program);

    return 0;
}
