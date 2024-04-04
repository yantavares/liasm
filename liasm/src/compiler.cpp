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
    std::vector<uint16_t> RAM(MEMORY_SIZE);    // Simulated memory -> 2^16 16-bit words
    std::vector<std::string> ROM(MEMORY_SIZE); // Stores the program token by token
    // TODO change instructions to uint16_t instead of string

    std::unordered_map<std::string, u_int16_t> labels; // Labels for jumps

    // First pass: builds the label map and stores the lines of the program
    FirstPassAnalyzer analyzer(RAM, labels, ROM);
    analyzer.analyse(file);
    analyzer.printLabels();

    // Second pass: executes the program
    SecondPassExecutor executor(RAM, labels, ROM);
    executor.execute();

    return 0;
}
