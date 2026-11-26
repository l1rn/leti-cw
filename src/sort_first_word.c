#include "sort_first_word.h"
#include <stdlib.h>
#include <wchar.h>

int len_first_word(const wchar_t *str)
{
    size_t end = wcscspn(str, L" \"\',/\n\t;:.!?()[]{}&+-|~<>`\r\v\f");

    return end;
}

int cmp_first_word(const void *a, const void *b)
{
    Sentence *pa = (Sentence *)a;
    const wchar_t *s1 = pa->data;
    Sentence *pb = (Sentence *)b;
    const wchar_t *s2 = pb->data;

    int s1_len = len_first_word(s1);
    int s2_len = len_first_word(s2);

    if (s1_len < s2_len) return -1;
    if (s1_len > s2_len) return 1;
    return 0;
}

void sort_by_first_word(vector_t *v)
{
    if (v == NULL || v->size < 2) {
        return;
    }
    qsort(v->elements, v->size, sizeof(Sentence), cmp_first_word);
}
