#ifndef SECONDPASSEXECUTOR_HPP
#define SECONDPASSEXECUTOR_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

class SecondPassExecutor
{
public:
    SecondPassExecutor(std::unordered_map<std::string, u_int16_t> &memory,
                       std::unordered_map<std::string, u_int16_t> &labels,
                       std::unordered_map<u_int16_t, std::string> &program);

    // Executes the program
    int execute();

private:
    u_int16_t ACC = 0; // Accumulator
    u_int16_t PC = 0;  // Program Counter

    std::unordered_map<std::string, u_int16_t> &memory;
    std::unordered_map<std::string, u_int16_t> &labels;
    std::unordered_map<u_int16_t, std::string> &program;

    // Helper methods for executing instructions
    void executeInstruction(const std::string &instr);

    void input(const std::string &variable);
    void load(const std::string &variable);
    void add(const std::string &variable);
    void sub(const std::string &variable);
    void mult(const std::string &variable);
    void store(const std::string &variable);
    void output(const std::string &variable);
    void jumpZ(const std::string &label);
    void jumpP(const std::string &label);
    void jumpN(const std::string &label);
    void jump(const std::string &label);
};

#endif // SECONDPASSEXECUTOR_HPP
