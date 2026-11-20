#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <stddef.h>

typedef struct vector{
	char **elements;
	size_t size;
	size_t cap;
} vector_t;

vector_r *create_vector(void);
void delete_vector(vector_t *v);
int v_push(vector_t *v, char *el);

#endif // STRING_UTIL_H
