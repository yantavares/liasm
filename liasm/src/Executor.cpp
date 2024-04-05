#include "Executor.hpp"

Executor::Executor(std::unordered_map<std::string, u_int16_t> labels)
    : labels(labels)
{
    const std::streamsize elementSize = sizeof(u_int16_t);

    RAM = new std::fstream("./RAM.txt", std::ios::out | std::ios::binary | std::ios::ate);
    ROM = new std::fstream("./ROM.txt", std::ios::out | std::ios::binary | std::ios::ate);
}

int Executor::execute()
{
    u_int16_t instr;

    while (true)
    {
        instr = readValueFromFile(1, PC);

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
        input(readValueFromFile(1, PC + 1));
    else if (instr == 0x02) // LOAD
        load(readValueFromFile(1, PC + 1));
    else if (instr == 0x03) // ADD
        add(readValueFromFile(1, PC + 1));
    else if (instr == 0x04) // SUB
        sub(readValueFromFile(1, PC + 1));
    else if (instr == 0x05) // MULT
        mult(readValueFromFile(1, PC + 1));
    else if (instr == 0x06) // STORE
        store(readValueFromFile(1, PC + 1));
    else if (instr == 0x07) // OUTPUT
        output(readValueFromFile(1, PC + 1));
    else if (instr == 0x08) // JUMPZ
        jumpZ(readValueFromFile(1, PC + 1));
    else if (instr == 0x09) // JUMPP
        jumpP(readValueFromFile(1, PC + 1));
    else if (instr == 0x0A) // JUMPN
        jumpN(readValueFromFile(1, PC + 1));
    else if (instr == 0x0B) // JUMP
        jump(readValueFromFile(1, PC + 1));
    else
    {
        std::cerr << "Invalid instruction: " << instr << " at address " << PC << std::endl;
        throw std::runtime_error("Execution failed due to invalid instruction.");
    }
}

void Executor::input(u_int16_t variable)
{
    u_int16_t value;
    std::cout << "Enter a value for " << findKeyByValue(variable) << ": ";
    std::cin >> value;
    writeValueToFile(0, variable, value);
    PC += 2;
}

void Executor::load(u_int16_t variable)
{
    ACC = readValueFromFile(0, variable);
    PC += 2;
}

void Executor::add(u_int16_t variable)
{
    ACC += readValueFromFile(0, variable);
    PC += 2;
}

void Executor::sub(u_int16_t variable)
{
    ACC -= readValueFromFile(0, variable);
    PC += 2;
}

void Executor::mult(u_int16_t variable)
{
    ACC *= readValueFromFile(0, variable);
    PC += 2;
}

void Executor::store(u_int16_t variable)
{
    writeValueToFile(0, variable, ACC);
    PC += 2;
}

void Executor::output(u_int16_t variable)
{
    std::cout << findKeyByValue(variable) << " = " << readValueFromFile(0, variable) << std::endl;
    PC += 2;
}

void Executor::jumpZ(u_int16_t addr)
{
    if (ACC == 0)
    {
        PC = addr;
    }
    else
        PC += 2;
}

void Executor::jumpP(u_int16_t addr)
{
    if (ACC > 0)
    {
        PC = addr;
    }
    else
        PC += 2;
}

void Executor::jumpN(u_int16_t addr)
{
    if (ACC < 0)
    {
        PC = addr;
    }
    else
        PC += 2;
}

void Executor::jump(u_int16_t addr)
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

u_int16_t Executor::readValueFromFile(u_int16_t type, u_int16_t index)
{
    u_int16_t value;
    std::streampos pos = index * elementSize;

    switch (type)
    {
    case 0:
        RAM->seekg(pos);
        RAM->read(reinterpret_cast<char *>(&value), elementSize);
        break;
    case 1:
        ROM->seekg(pos);
        ROM->read(reinterpret_cast<char *>(&value), elementSize);
        break;
    }
    return value;
}

void Executor::writeValueToFile(u_int16_t type, u_int16_t index, u_int16_t value)
{
    switch (type)
    {
    case 0:
        std::streampos pos = index * elementSize;
        RAM->seekp(pos);
        RAM->write(reinterpret_cast<const char *>(&value), elementSize);
        break;

    case 1:
        std::streampos pos = index * elementSize;
        ROM->seekp(pos);
        ROM->write(reinterpret_cast<const char *>(&value), elementSize);
        break;
    }
}
