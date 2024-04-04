#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "FirstPassAnalyzer.hpp"
#include "SecondPassExecutor.hpp"

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

    constexpr size_t MEMORY_SIZE = 65536;      // For a 16-bit address space
    std::vector<uint16_t> memory(MEMORY_SIZE); // Simulated memory -> 2^16 16-bit words

    std::unordered_map<std::string, u_int16_t> labels;  // Labels for jumps
    std::unordered_map<u_int16_t, std::string> program; // Stores the program line by line

    // First pass: builds the label map and stores the lines of the program
    FirstPassAnalyzer analyzer(memory, labels, program);
    analyzer.analyse(file);
    analyzer.printLabels();

    for (const auto &[address, instr] : program)
    {
        std::cout << address << ": " << instr << std::endl;
    }

    // Second pass: executes the program
    SecondPassExecutor executor(memory, labels, program);
    executor.execute();

    return 0;
}
