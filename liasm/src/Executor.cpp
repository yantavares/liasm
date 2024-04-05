#include "Executor.hpp"

Executor::Executor(std::unordered_map<std::string, u_int16_t> labels)
    : labels(labels), elementSize(16) // 16 bits per element
{

    RAM = std::make_unique<std::fstream>("./RAM.txt", std::ios::in | std::ios::out | std::ios::binary);
    ROM = std::make_unique<std::fstream>("./ROM.txt", std::ios::in | std::ios::out | std::ios::binary);

    if (!RAM->is_open())
    {
        throw std::runtime_error("Failed to open RAM.txt");
    }
    if (!ROM->is_open())
    {
        throw std::runtime_error("Failed to open ROM.txt");
    }
}

int Executor::execute()
{
    u_int16_t instr;

    while (true)
    {
        instr = readValueFromFile(1, PC);

        if (instr == 0x0E) // STOP
        {
            break;
        }

        if (instr > 0x0E || instr < 0x01)
        {
            std::cerr << "Invalid instruction: " << instr << " at address " << PC << std::endl;
            throw std::runtime_error("Execution failed due to invalid instruction.");
        }

        executeInstruction(instr);
    }
    return 0;
}

void Executor::executeInstruction(u_int16_t &instr)
{
    if (instr == 0x01)
        addI(readValueFromFile(1, PC + 1)); // ADD
    else if (instr == 0x02)
        subI(readValueFromFile(1, PC + 1)); // SUB
    else if (instr == 0x03)
        multI(readValueFromFile(1, PC + 1)); // MUL
    else if (instr == 0x04)
        divI(readValueFromFile(1, PC + 1)); // DIV
    else if (instr == 0x05)
        jumpI(readValueFromFile(1, PC + 1)); // JMP
    else if (instr == 0x06)
        jumpNI(readValueFromFile(1, PC + 1)); // JMPN
    else if (instr == 0x07)
        jumpPI(readValueFromFile(1, PC + 1)); // JMPP
    else if (instr == 0x08)
        jumpZI(readValueFromFile(1, PC + 1)); // JMPZ
    else if (instr == 0x09)
        copyI(readValueFromFile(1, PC + 1), readValueFromFile(1, PC + 2)); // COPY
    else if (instr == 0x0A)
        loadI(readValueFromFile(1, PC + 1)); // LOAD
    else if (instr == 0x0B)
        storeI(readValueFromFile(1, PC + 1)); // STORE
    else if (instr == 0x0C)
        inputI(readValueFromFile(1, PC + 1)); // INPUT
    else if (instr == 0x0D)
        outputI(readValueFromFile(1, PC + 1)); // OUTPUT

    else
    {
        std::cerr << "Invalid instruction: " << instr << " at address " << PC << std::endl;
        throw std::runtime_error("Execution failed due to invalid instruction.");
    }
}

void Executor::inputI(u_int16_t variable)
{
    u_int16_t value;
    std::cout << "Enter a value for " << findKeyByValue(variable) << ": ";
    std::cin >> value;
    writeValueToFile(0, variable, value);
    PC += 2;
}

void Executor::loadI(u_int16_t variable)
{
    ACC = readValueFromFile(0, variable);
    PC += 2;
}

void Executor::addI(u_int16_t variable)
{
    ACC += readValueFromFile(0, variable);
    PC += 2;
}

void Executor::subI(u_int16_t variable)
{
    ACC -= readValueFromFile(0, variable);
    PC += 2;
}

void Executor::multI(u_int16_t variable)
{
    ACC *= readValueFromFile(0, variable);
    PC += 2;
}

void Executor::divI(u_int16_t variable)
{
    ACC /= readValueFromFile(0, variable);
    PC += 2;
}

void Executor::storeI(u_int16_t variable)
{
    writeValueToFile(0, variable, ACC);
    PC += 2;
}

void Executor::outputI(u_int16_t variable)
{
    std::cout << findKeyByValue(variable) << " = " << readValueFromFile(0, variable) << std::endl;
    PC += 2;
}

void Executor::jumpZI(u_int16_t addr)
{
    if (ACC == 0)
    {
        PC = addr;
    }
    else
        PC += 2;
}

void Executor::jumpPI(u_int16_t addr)
{
    if (ACC > 0)
    {
        PC = addr;
    }
    else
        PC += 2;
}

void Executor::jumpNI(u_int16_t addr)
{
    if (ACC < 0)
    {
        PC = addr;
    }
    else
        PC += 2;
}

void Executor::jumpI(u_int16_t addr)
{
    PC = addr;
}

void Executor::copyI(u_int16_t source, u_int16_t dest)
{
    writeValueToFile(0, dest, readValueFromFile(0, source)); // 0 -> RAM
    PC += 3;
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
    u_int16_t value = 0;
    std::string binaryString;

    // Calculate the position in the file, assuming each line is 17 characters (16 bits + newline)
    std::streampos pos = index * (elementSize + 1); // +1 for the newline character

    switch (type)
    {
    case 0:
        RAM->seekg(pos);
        std::getline(*RAM, binaryString); // Read the line into the string
        break;

    case 1:
        ROM->seekg(pos);
        std::getline(*ROM, binaryString); // Read the line into the string
        break;
    }

    // Convert the binary string back to a uint16_t value
    if (!binaryString.empty())
    {
        value = static_cast<u_int16_t>(std::bitset<16>(binaryString).to_ulong());
    }

    return value;
}

void Executor::writeValueToFile(u_int16_t type, u_int16_t index, u_int16_t value)
{
    // Convert the value to a binary string
    std::string binaryString = std::bitset<16>(value).to_string();

    // Calculate the position in the file.
    // Note: This calculation assumes each line in the file is 16 characters long plus a newline character.
    std::streampos pos = index * (elementSize + 1); // +1 for the newline character

    switch (type)
    {
    case 0:
        RAM->seekp(pos);
        *RAM << binaryString << std::endl; // Write the binary string with a newline
        break;

    case 1:
        ROM->seekp(pos);
        *ROM << binaryString << std::endl; // Write the binary string with a newline
        break;
    }
}
