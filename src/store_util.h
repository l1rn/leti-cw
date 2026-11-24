#ifndef STORE_UTIL_H
#define STORE_UTIL_H

#include <wchar.h>

typedef struct word_entry {
	wchar_t *value; 
	int *arr;
	size_t size;
	size_t cap;
} word_entry_t;

typedef struct {
	word_entry_t *items;
	size_t size;
	size_t cap;
} word_entry_list;

word_entry_t *create_word_entry(wchar_t *v);

int e_push_back(word_entry_t *e, int idx);
int e_read_sentence(wchar_t *s, int idx, word_entry_list *l);

void free_word_list(word_entry_list *l);

int word_list_init(word_entry_list *l);

#endif // STORE_UTIL_H
