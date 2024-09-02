# Makefile for compiling, disassembling, cleaning, and running the C++ program

# Variables
CPP = g++
CFLAGS =
TARGET = multiply
SRC = multiply.cpp
DISASS = $(TARGET).asm

all: $(TARGET)

# Rule for "make" command
$(TARGET): $(SRC)
		$(CPP) $(CFLAGS) -o $(TARGET) $(SRC)

# Disassemble binary file, only showing the main function, then put it in a new file named $(TARGET).asm
dump: $(TARGET)
		objdump -d --disassemble=main $(TARGET).exe > $(DISASS)

# Clean generated files from compiled file and disassembled file
clean:
		del /Q $(TARGET).exe $(DISASS)

# Rule to run compiled executable
run: $(TARGET)
		./$(TARGET)

.PHONY: all dump clean run