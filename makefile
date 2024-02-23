# General macros
CC = gcc
FLAGS = -Wall 

# Default target: compile all programs (means StrList)
all: StrList 

# Program file compiling rules
StrList: Main.c StrList.c
	$(CC) $(FLAGS) Main.c StrList.c -o StrList

# Clean-up
clean:
	rm -f *.o *.bin StrList

.PHONY: clean
