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

    try
    {
        FirstPassAnalyzer analyzer(labels);
        analyzer.analyse(file);
        analyzer.printLabels();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << " FIRST PASS ERROR!" << '\n';
        return 1;
    }
    // Makes sure to reset the file to the beginning
    file.clear();
    file.seekg(0, std::ios::beg);

    file.open(argv[1]);

    try
    {
        SecondPassAnalyzer analyzer2(labels);
        analyzer2.analyse(file);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << " SECOND PASS ERROR!" << '\n';
        return 1;
    }

    file.close();

    try
    {
        Assembler executor(labels);
        executor.execute();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << " RUNTIME ERROR!" << '\n';
        return 1;
    }

    return 0;
}
