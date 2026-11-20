CC=gcc
CFLAGS=-Wall -Wextra

all: cw run

cw: main.o delete_first_word.o string_util.o sort_first_word.o task_manager.o alphabet.o
	$(CC) $(CFLAGS) $^ -o $@
run: cw
	./cw

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o cw

.PHONY: all clean run
