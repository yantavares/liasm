#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "FirstPassAnalyzer.hpp"
#include "Assembler.hpp"
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

    std::unordered_map<std::string, u_int16_t> labels; // Labels

    FirstPassAnalyzer analyzer(labels);
    analyzer.analyse(file);
    analyzer.printLabels();

    file.open(argv[1]);

    SecondPassAnalyzer analyzer2(labels);
    analyzer2.analyse(file);

    Assembler executor(labels);
    executor.execute();

    return 0;
}
