CC = g++
CFLAGS = -Wall -std=c++14 -I includes
SRCDIR = src
BINDIR = bin
SOURCES = $(wildcard $(SRCDIR)/*.cpp) compiler.cpp
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BINDIR)/%.o)
TARGET = licc

.PHONY: all clean create_memories

all: create_memories $(TARGET)

create_memories:
	/opt/anaconda3/bin/python /Users/yantavares/sb/liasm/utils/createMemories.py

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(BINDIR)/%.o: $(SRCDIR)/%.cpp | $(BINDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR):
	mkdir -p $(BINDIR)

run: all
	./$(TARGET) $(ARGS)

clean:
	rm -rf $(BINDIR) $(TARGET)
