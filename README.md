# Linguagem Inventada - liasm (EN)

![Stars](https://img.shields.io/github/stars/yantavares/liasm)
[![License: Unlicense](https://img.shields.io/badge/license-Unlicense-blue.svg)](http://unlicense.org/)

For the Portuguese version, click [here](README_PTBR.md).

Welcome to the repository of the Linguagem Inventada, a simulation machine that allows assembling and running programs written in the "Linguagem Inventada" or `liasm`, created in the University of Brasília (UnB).

## Hypothetical Machine Description

The `liasm` environment is designed to emulate a simple computer architecture. The hypothetical machine at its core has the following components:

- **ACC**: A 16-bit accumulator register for arithmetic and logic operations.
- **PC**: A 16-bit program counter register that points to the next instruction.
- **Memory**: A memory with \( 2^{16} \) words, each of 16 bits.

This machine recognizes three instruction formats:

- Format 1: Single Opcode
- Format 2: Opcode followed by one address
- Format 3: Opcode followed by two addresses

The instruction set is designed to be minimal yet complete, allowing the implementation of a wide range of algorithms.

## liasm Assembly Language

Although simple, `liasm` can be considered a Turing-complete language. It has a set of instructions and directives that allow the programmer to write complex programs. The following table lists the available instructions:

| Mnemonic | Opcode Numeric | Size (words) | Action                 |
| -------- | -------------- | ------------ | ---------------------- |
| ADD      | 01             | 2            | ACC <- ACC + mem(OP)   |
| SUB      | 02             | 2            | ACC <- ACC - mem(OP)   |
| MUL      | 03             | 2            | ACC <- ACC \* mem(OP)  |
| DIV      | 04             | 2            | ACC <- ACC ÷ mem(OP)   |
| JMP      | 05             | 2            | PC <- OP               |
| JMPN     | 06             | 2            | If ACC<0 then PC <- OP |
| JMPP     | 07             | 2            | If ACC>0 then PC <- OP |
| JMPZ     | 08             | 2            | If ACC=0 then PC <- OP |
| COPY     | 09             | 3            | mem(OP2) <- mem(OP1)   |
| LOAD     | 10             | 2            | ACC <- mem(OP)         |
| STORE    | 11             | 2            | mem(OP) <- ACC         |
| INPUT    | 12             | 2            | mem(OP) <- input       |
| OUTPUT   | 13             | 2            | output <- mem(OP)      |
| STOP     | 14             | 1            | Suspends execution     |
| THROW    | 15             | 1            | Throws an exception    |
| NOP      | 16             | 1            | Increments PC by 1     |

Directives:

- CONST: Allocates a constant value to a memory address.
  Example: `N3: CONST 1 ; Allocates 1 to N3`
- SPACE: Allocates memory space to an address without initializing it.
  Example: `N1: SPACE ; Allocates memory to N1 address`

Comments:

- Comments in the `liasm` assembly code start with a semicolon (`;`).
  Everything following the `;` on a line is considered a comment and is ignored by the assembler.

## Compiler Workflow

The `liasm` compiler operates in two passes:

1. **First Pass**: The compiler reads the source `.liasm` file to build a table of labels, which is used to resolve addresses during the assembly process. During this phase, the compiler also performs lexical analysis to identify any syntax errors in the source code.

2. **Second Pass**: With the label table constructed, the compiler reads the source file a second time, this time translating the assembly instructions into binary code. The compiler also performs semantic checks to ensure the integrity of the program, such as validating instruction formats and detecting any undefined references.

## Project Structure

Here's an overview of the project structure to help you navigate and understand its components:

- **`liasm/`**: The main directory containing all the resources needed for the assembler and simulation.
  - **`bin/`**: Stores the compiled binaries of the assembler.
  - **`examples/`**: Contains examples of Inventive Assembly code for testing and learning.
  - **`includes/`**: Headers of libraries used by the assembler.
  - **`src/`**: Source code of the assembler.
  - **`tests/`**: Automated tests.
  - **`utils/`**: Auxiliary tools.
  - **`compiler.cpp`**: The main file of the compiler.
  - **`Makefile`**: To compile the project using `make`.
  - **`RAM.txt`** and **`ROM.txt`**: Simulate RAM and ROM memory files, respectively.
- **`.gitignore`**: List of files/directories to ignore in versioning.
- **`README.md`**: Documentation (this file).

## Getting Started

### Prerequisites

Before you begin, ensure the following tools are installed on your system:

- **`make`**: Utility for automation of compilation.
- **`g++`**: The C++ compiler from the GNU Compiler Collection (GCC).

The assembler was tested succesafuly on OSX and Linux (both x86 and ARM).

### Assembling and Running Programs with `licc`

To compile the `licc` assembler:

1. **Navigate to the project directory**:

   ```bash
   cd liasm/
   ```

2. **Compile the assembler** using the `make` command:

   ```bash
    make
   ```

Or you can just use the precompiled binary in the `liasm` directory.

#### Using Makefile

After compiling the assembler:

- **To assemble a program**, replace `<file path>` with your `.asm` file:

  ```bash
  ./licc <file path>
  ```

- **Optional**: You can also set the mode to `debug` to see the generated labels and verbose output.

  ```bash
  ./licc <file path> debug
  ```

#### Direct Execution with `make run`

- **To compile the assembler and execute directly**, replace `<file path>` with the path of your `.asm` file:

  ```bash
  make run FILE=<file path>
  ```

- **Optional**: You can also set the mode to `debug` to see the generated labels and verbose output.

  ```bash
  make run FILE=<file path> MODE=debug
  ```

### Running Tests

To ensure the assembler is working correctly:

```bash
make test
```

This command compiles the assembler and runs all the tests in the `tests/` folder.

## License

This project is under the UNLICENSE, allowing complete freedom for use, modification, and distribution.
