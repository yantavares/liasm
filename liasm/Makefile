CC = g++
CFLAGS = -Wall -std=c++11

all: scanner parser compiler

scanner: scanner.cpp scanner.h
    $(CC) $(CFLAGS) -o scanner scanner.cpp

parser: parser.cpp parser.h
    $(CC) $(CFLAGS) -o parser parser.cpp

compiler: compiler.cpp compiler.h
    $(CC) $(CFLAGS) -o compiler compiler.cpp

clean:
    rm -f scanner parser compiler