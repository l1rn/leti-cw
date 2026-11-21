#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <stddef.h>
#include <wchar.h>

typedef struct vector{
	wchar_t **elements;
	size_t size;
	size_t cap;
} vector_t;

wchar_t *get_wc(char *s);
void free_wc_string(wchar_t *wc_s);

vector_t *create_vector(void);
void delete_vector(vector_t *v);

int v_push_back(vector_t *v, wchar_t *el);
int v_remove_at(vector_t *v, size_t idx);
int v_el_size(wchar_t *str);

void sort_by_first_word(vector_t *v);
void print_v(vector_t *v);
vector_t *read_sentences(void);

#endif // STRING_UTIL_H
