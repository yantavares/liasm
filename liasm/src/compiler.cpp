#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "FirstPassAnalyzer.hpp"
#include "Executor.hpp"
#include "SecondPassAnalyzer.hpp"

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

    constexpr size_t MEMORY_SIZE = 65536;    // For a 16-bit address space
    std::vector<u_int16_t> RAM(MEMORY_SIZE); // Simulated memory -> 2^16 16-bit words
    std::vector<u_int16_t> ROM(MEMORY_SIZE); // Stores the program token by token

    std::unordered_map<std::string, u_int16_t> labels; // Labels

    FirstPassAnalyzer analyzer(labels);
    analyzer.analyse(file);
    analyzer.printLabels();

    file.open(argv[1]);

    SecondPassAnalyzer analyzer2(RAM, ROM, labels);
    analyzer2.analyse(file);

    Executor executor(RAM, ROM, labels);
    executor.execute();

    return 0;
}
