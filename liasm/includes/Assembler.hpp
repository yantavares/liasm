#ifndef SECONDPASSEXECUTOR_HPP
#define SECONDPASSEXECUTOR_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <memory>

class Assembler
{
public:
    Assembler(std::unordered_map<std::string, u_int16_t> labels);

    // Executes the program
    int execute();

private:
    u_int16_t ACC = 0; // Accumulator
    u_int16_t PC = 0;  // Program Counter

    std::unordered_map<std::string, u_int16_t> labels;

    // Helper methods for executing instructions
    void executeInstruction(u_int16_t &instr);
    std::string findKeyByValue(u_int16_t &addr);

    void inputI(u_int16_t variable);
    void loadI(u_int16_t variable);
    void addI(u_int16_t variable);
    void subI(u_int16_t variable);
    void divI(u_int16_t variable);
    void multI(u_int16_t variable);
    void storeI(u_int16_t variable);
    void outputI(u_int16_t variable);
    void jumpZI(u_int16_t label);
    void jumpPI(u_int16_t label);
    void jumpNI(u_int16_t label);
    void jumpI(u_int16_t label);
    void copyI(u_int16_t source, u_int16_t dest);

    const std::streamsize elementSize;
    u_int16_t readValueFromFile(u_int16_t type, u_int16_t index);
    void writeValueToFile(u_int16_t type, u_int16_t index, u_int16_t value);

protected:
    std::unique_ptr<std::fstream> RAM;
    std::unique_ptr<std::fstream> ROM;
};

#endif // SECONDPASSEXECUTOR_HPP
