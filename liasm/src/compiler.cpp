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

    std::unordered_map<std::string, u_int16_t> memory;  // Simulated memory
    std::unordered_map<std::string, u_int16_t> labels;  // Labels for jumps
    std::unordered_map<u_int16_t, std::string> program; // Stores the program line by line

    // First pass: builds the label map and stores the lines of the program
    FirstPassAnalyzer analyzer(memory, labels, program);
    analyzer.analyse(file);
    analyzer.printLabels();

    // Second pass: executes the program
    SecondPassExecutor executor(memory, labels, program);
    executor.execute();

    return 0;
}
