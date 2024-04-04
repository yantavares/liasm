#include "Executor.hpp"

Executor::Executor(std::vector<u_int16_t> &RAM,
                   std::vector<u_int16_t> &ROM,
                   std::unordered_map<std::string, u_int16_t> labels)

    : RAM(RAM), ROM(ROM), labels(labels)
{
}

int Executor::execute()
{
    u_int16_t instr;

    while (true)
    {
        instr = ROM[PC];

        if (instr == 0x00) // STOP
        {
            break;
        }

        if (instr > 0x0C || instr < 0x00)
        {
            std::cerr << "Invalid instruction at address " << PC << std::endl;
        }

        executeInstruction(instr);
    }
    return 0;
}

void Executor::executeInstruction(u_int16_t &instr)
{
    if (instr == 0x01) // INPUT
        input(ROM[PC + 1]);
    else if (instr == 0x02) // LOAD
        load(ROM[PC + 1]);
    else if (instr == 0x03) // ADD
        add(ROM[PC + 1]);
    else if (instr == 0x04) // SUB
        sub(ROM[PC + 1]);
    else if (instr == 0x05) // MULT
        mult(ROM[PC + 1]);
    else if (instr == 0x06) // STORE
        store(ROM[PC + 1]);
    else if (instr == 0x07) // OUTPUT
        output(ROM[PC + 1]);
    else if (instr == 0x08) // JUMPZ
        jumpZ(ROM[PC + 1]);
    else if (instr == 0x09) // JUMPP
        jumpP(ROM[PC + 1]);
    else if (instr == 0x0A) // JUMPN
        jumpN(ROM[PC + 1]);
    else if (instr == 0x0B) // JUMP
        jump(ROM[PC + 1]);
    else
    {
        std::cerr << "Invalid instruction: " << instr << " at address " << PC << std::endl;
        throw std::runtime_error("Execution failed due to invalid instruction.");
    }
}

void Executor::input(u_int16_t &variable)
{
    std::cout << "Enter a value for " << findKeyByValue(variable) << ": ";
    std::cin >> RAM[variable];
    PC += 2;
}

void Executor::load(u_int16_t &variable)
{
    ACC = RAM[variable];
    PC += 2;
}

void Executor::add(u_int16_t &variable)
{
    ACC += RAM[variable];
    PC += 2;
}

void Executor::sub(u_int16_t &variable)
{
    ACC -= RAM[variable];
    PC += 2;
}

void Executor::mult(u_int16_t &variable)
{
    ACC *= RAM[variable];
    PC += 2;
}

void Executor::store(u_int16_t &variable)
{
    RAM[variable] = ACC;
    PC += 2;
}

void Executor::output(u_int16_t &variable)
{
    std::cout << findKeyByValue(variable) << " = " << RAM[variable] << std::endl;
    PC += 2;
}

void Executor::jumpZ(u_int16_t &addr)
{
    if (ACC == 0)
    {
        PC = addr;
    }
    else
        PC += 2;
}

void Executor::jumpP(u_int16_t &addr)
{
    if (ACC > 0)
    {
        PC = addr;
    }
    else
        PC += 2;
}

void Executor::jumpN(u_int16_t &addr)
{
    if (ACC < 0)
    {
        PC = addr;
    }
    else
        PC += 2;
}

void Executor::jump(u_int16_t &addr)
{
    PC = addr;
}

std::string Executor::findKeyByValue(u_int16_t &addr)
{
    for (const auto &pair : labels)
    {
        if (pair.second == addr)
        {
            return pair.first;
        }
    }
    return ""; // Return an empty string if no key is found
}