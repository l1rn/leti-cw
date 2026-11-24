#include "sort_first_word.h"
#include <stdlib.h>
#include <wchar.h>

int len_first_word(const wchar_t *str)
{
    wchar_t *buffer;
    wchar_t *cp = wcsdup(str);
    wchar_t *t = wcstok(cp, L" ", &buffer);
    int len = wcslen(t);
    free(cp);
    return len;
}

int cmp_first_word(const void *a, const void *b)
{
    wchar_t **pa = (wchar_t **)a;
    const wchar_t *s1 = *pa;
    wchar_t **pb = (wchar_t **)b;
    const wchar_t *s2 = *pb;

    int s1_len = len_first_word(s1);
    int s2_len = len_first_word(s2);
    return s1_len > s2_len;
}

void sort_by_first_word(vector_t *v)
{
    if (v == NULL || v->size < 2) {
        return;
    }
    qsort(v->elements, v->size, sizeof(char *), cmp_first_word);
}
