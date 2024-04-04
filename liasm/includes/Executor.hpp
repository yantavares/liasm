#ifndef SECONDPASSEXECUTOR_HPP
#define SECONDPASSEXECUTOR_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class Executor
{
public:
    Executor(std::vector<u_int16_t> &RAM,
             std::vector<u_int16_t> &ROM,
             std::unordered_map<std::string, u_int16_t> labels);

    // Executes the program
    int execute();

private:
    u_int16_t ACC = 0; // Accumulator
    u_int16_t PC = 0;  // Program Counter

    std::vector<u_int16_t> &RAM;
    std::vector<u_int16_t> &ROM;
    std::unordered_map<std::string, u_int16_t> labels;

    // Helper methods for executing instructions
    void executeInstruction(u_int16_t &instr);
    std::string findKeyByValue(u_int16_t &addr);

    void input(u_int16_t &variable);
    void load(u_int16_t &variable);
    void add(u_int16_t &variable);
    void sub(u_int16_t &variable);
    void mult(u_int16_t &variable);
    void store(u_int16_t &variable);
    void output(u_int16_t &variable);
    void jumpZ(u_int16_t &label);
    void jumpP(u_int16_t &label);
    void jumpN(u_int16_t &label);
    void jump(u_int16_t &label);
};

#endif // SECONDPASSEXECUTOR_HPP
