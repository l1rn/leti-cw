#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <stddef.h>

typedef struct vector{
	char **elements;
	size_t size;
	size_t cap;
} vector_t;

vector_t *create_vector(void);
void delete_vector(vector_t *v);

int v_push_back(vector_t *v, char *el);
int v_remove_at(vector_t *v, size_t idx);
int v_el_size(char *str);

void sort_by_first_word(vector_t *v);
void print_v(vector_t *v);

#endif // STRING_UTIL_H
