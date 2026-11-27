#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <stddef.h>
#include <wchar.h>

typedef struct Sentence {
    wchar_t *data;
    size_t len;
} Sentence;

typedef struct Text {
    Sentence *elements;
    size_t size;
    size_t cap;
} Text;

typedef Text vector_t;

int is_terminator(wchar_t wc);
wchar_t *get_wc(char *s);
void free_wc_string(wchar_t *wc_s);

vector_t *create_vector(void);
void delete_vector(vector_t *v);

int v_push_back(vector_t *v, wchar_t *el);
int v_remove_at(vector_t *v, size_t idx);
int v_replace_at(vector_t *v, size_t idx, wchar_t *new_el);
int v_el_size(wchar_t *str);
int v_in_vector(vector_t *v, wchar_t *s);

int v_s_lower_cmp(wchar_t *s1, wchar_t *s2, size_t s2_size);

#endif // STRING_UTIL_H
