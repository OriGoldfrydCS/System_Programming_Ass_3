CC = gcc
FLAGS = -Wall 

all: StrList

StrList: Main.c StrList.c
	$(CC) $(FLAGS) Main.c StrList.c -o StrList

clean:
	rm -f *.o *.bin StrList

.PHONY: clean
