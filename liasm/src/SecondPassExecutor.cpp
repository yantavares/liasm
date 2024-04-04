#include "SecondPassExecutor.hpp"

SecondPassExecutor::SecondPassExecutor(std::vector<u_int16_t> &RAM,
                                       std::vector<std::string> &ROM,
                                       std::unordered_map<std::string, u_int16_t> &labels)

    : RAM(RAM), ROM(ROM), labels(labels)
{
}

int SecondPassExecutor::execute()
{
    std::string instr;

    while (true)
    {
        instr = ROM[PC];

        if (instr == "STOP")
        {
            break;
        }

        if (instr.empty())
        {
            std::cerr << "Invalid instruction at address " << PC << std::endl;
        }

        executeInstruction(instr);
    }
    return 0;
}

void SecondPassExecutor::executeInstruction(const std::string &instr)
{
    std::string label = ROM[PC + 1];

    if (instr == "INPUT")
        input(label);
    else if (instr == "LOAD")
        load(label);
    else if (instr == "ADD")
        add(label);
    else if (instr == "SUB")
        sub(label);
    else if (instr == "MULT")
        mult(label);
    else if (instr == "STORE")
        store(label);
    else if (instr == "OUTPUT")
        output(label);
    else if (instr == "JUMPZ")
        jumpZ(label);
    else if (instr == "JUMPP")
        jumpP(label);
    else if (instr == "JUMPN")
        jumpN(label);
    else if (instr == "JUMP")
        jump(label);
    else
    {
        std::cerr << "Invalid instruction: " << instr << " at address " << PC << std::endl;
        throw std::runtime_error("Execution failed due to invalid instruction.");
    }
}

void SecondPassExecutor::input(const std::string &variable)
{
    std::cout << "Enter a value for " << variable << ": ";
    std::cin >> RAM[labels[variable]];
    PC += 2;
}

void SecondPassExecutor::load(const std::string &variable)
{
    ACC = RAM[labels[variable]];
    PC += 2;
}

void SecondPassExecutor::add(const std::string &variable)
{
    ACC += RAM[labels[variable]];
    PC += 2;
}

void SecondPassExecutor::sub(const std::string &variable)
{
    ACC -= RAM[labels[variable]];
    PC += 2;
}

void SecondPassExecutor::mult(const std::string &variable)
{
    ACC *= RAM[labels[variable]];
    PC += 2;
}

void SecondPassExecutor::store(const std::string &variable)
{
    RAM[labels[variable]] = ACC;
    PC += 2;
}

void SecondPassExecutor::output(const std::string &variable)
{
    std::cout << variable << " = " << RAM[labels[variable]] << std::endl;
    PC += 2;
}

void SecondPassExecutor::jumpZ(const std::string &label)
{
    if (ACC == 0)
    {
        PC = labels[label];
    }
    else
        PC += 2;
}

void SecondPassExecutor::jumpP(const std::string &label)
{
    if (ACC > 0)
    {
        PC = labels[label];
    }
    else
        PC += 2;
}

void SecondPassExecutor::jumpN(const std::string &label)
{
    if (ACC < 0)
    {
        PC = labels[label];
    }
    else
        PC += 2;
}

void SecondPassExecutor::jump(const std::string &label)
{
    PC = labels[label];
}
