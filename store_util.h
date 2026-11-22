#ifndef STORE_UTIL_H
#define STORE_UTIL_H

#include <wchar.h>

typedef struct word_entry {
	wchar_t *value; 
	int *arr;
	size_t size;
	size_t cap;
} word_entry_t;

word_entry_t *create_word_entry(wchar_t *v);

int e_push_back(word_entry_t *e, int idx);
int e_read_sentence(wchar_t *s);

#endif // STORE_UTIL_H
