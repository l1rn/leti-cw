CC=gcc

all:
	$(CC) -Wall -Wextra main.c delete_first_word.c -o main
	./main
