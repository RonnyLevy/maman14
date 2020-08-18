# build an executable customized assembler - maman14

# compiler flags:

# -Wall : enables all compiler's warning messages

# -ansi : determine the language standard to be C

# pedantic: generates more warnings

CC = gcc

TARGET = assembler

DEPS = file_utils.h language_structure.h command_hash_table.h

OBJ = main.o file_utils.o language_structure.o command_hash_table.o

CFLAGS = -Wall -ansi -pedantic -I.

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)	
