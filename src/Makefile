CC=gcc
CFLAGS=-Wall -Wextra
DEBUG_FLAGS=-fno-common -std=c11 -g -Wall -Werror -fsanitize=address -lpng -lm
OBJS=main.o delete_first_word.o string_util.o sort_first_word.o task_manager.o alphabet.o vowel_changer.o digit_to_alpha.o store_util.o

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
