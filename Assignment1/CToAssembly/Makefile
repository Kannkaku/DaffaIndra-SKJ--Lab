# makefile for compiling, disassembling, cleaning, and running the C++ program

# Variables
CPP = g++
CFLAGS =
TARGET = add
SRC = add.cpp
DISASS = $(TARGET).asm

all: $(TARGET)

#rule for "make" command
$(TARGET): $(SRC)
		$(CPP) $(CFLAGS) -o $(TARGET) $(SRC)

# disassemble binary file then put it in a new file named $(TARGET).asm
dump: $(TARGET)
		objdump -d $(TARGET).exe > $(DISASS)

# clean generated file from compiled file and disassembled file
clean:
		rm -f $(TARGET) $(DISASS)

# rule to run compiled executable
run: $(TARGET)
		./$(TARGET)

.PHONY: all dump clean run