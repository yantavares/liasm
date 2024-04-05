#ifndef SECONDPASSEXECUTOR_HPP
#define SECONDPASSEXECUTOR_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <bitset>

class Executor
{
public:
    Executor(std::unordered_map<std::string, u_int16_t> labels);

    // Executes the program
    int execute();

private:
    u_int16_t ACC = 0; // Accumulator
    u_int16_t PC = 0;  // Program Counter

    std::unordered_map<std::string, u_int16_t> labels;

    // Helper methods for executing instructions
    void executeInstruction(u_int16_t &instr);
    std::string findKeyByValue(u_int16_t &addr);

    void input(u_int16_t variable);
    void load(u_int16_t variable);
    void add(u_int16_t variable);
    void sub(u_int16_t variable);
    void mult(u_int16_t variable);
    void store(u_int16_t variable);
    void output(u_int16_t variable);
    void jumpZ(u_int16_t label);
    void jumpP(u_int16_t label);
    void jumpN(u_int16_t label);
    void jump(u_int16_t label);

    const std::streamsize elementSize;
    u_int16_t readValueFromFile(u_int16_t type, u_int16_t index);
    void writeValueToFile(u_int16_t type, u_int16_t index, u_int16_t value);

protected:
    std::fstream *RAM;
    std::fstream *ROM;
};

#endif // SECONDPASSEXECUTOR_HPP
