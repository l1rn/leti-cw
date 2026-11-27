CC=gcc
CFLAGS=-Wall -Wextra
DEBUG_FLAGS=-fno-common -std=c11 -g -Wall -Werror -fsanitize=address -lpng -lm
OBJS=main.o task_first.o task_second.o task_third.o task_four.o task_five_map.o string_util.o process_manager.o alphabet.o io.o

all: cw

cw: $(OBJS)
	$(CC) $(CFLAGS) $^ -o cw

debug: $(OBJS)
	$(CC) $(DEBUG_FLAGS) $^ -o $@

run: cw
	./cw

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o cw debug *.txt

.PHONY: all clean run debug
