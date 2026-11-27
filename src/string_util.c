#include "string_util.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

int v_s_lower_cmp(wchar_t *s1, wchar_t *s2, size_t s2_size)
{
    if (wcslen(s1) != s2_size)
        return 0;
    for (size_t i = 0; i < s2_size; i++) {
        if (towlower(s1[i]) != towlower(s2[i])) {
            return 0;
        }
    }
    return 1;
}

wchar_t *get_wc(char *c)
{
    if (c == NULL)
        return NULL;

    size_t c_size = mbstowcs(NULL, c, 0);
    if (c_size == (size_t)-1) {
        return NULL;
    }

    size_t slots = c_size + 1;
    wchar_t *wc = malloc(slots * sizeof(wchar_t));
    if (wc == NULL) {
        return NULL;
    }

    size_t n = mbstowcs(wc, c, slots);
    if (n == (size_t)-1) {
        free(wc);
        return NULL;
    }
    return wc;
}

int is_terminator(wchar_t wc)
{
    return wc == L'.' || wc == L'!' || wc == L'?';
}

void free_wc_string(wchar_t *wc_s)
{
    free(wc_s);
}

vector_t *create_vector(void)
{
    vector_t *v = malloc(sizeof(vector_t));
    if (v == NULL) {
        return NULL;
    }
    v->size = 0;
    v->cap = 4;
    v->elements = malloc(v->cap * sizeof(Sentence));
    if (v->elements == NULL) {
        free(v);
        return NULL;
    }
    return v;
}

void delete_vector(vector_t *v)
{
    if (v == NULL) {
        return;
    }
    for (size_t i = 0; i < v->size; i++) {
        free(v->elements[i].data);
    }
    free(v->elements);
    free(v);
}

int resize_vector(vector_t *v)
{
    int new_cap = v->cap * 2;
    Sentence *tmp = realloc(v->elements, new_cap * sizeof(Sentence));

    if (tmp == NULL) {
        return -1;
    }
    v->elements = tmp;
    v->cap = new_cap;
    return 0;
}

int v_el_size(wchar_t *str)
{
    if (str == NULL) {
        return -1;
    }

    int count = 0;
    int flag = 0;
    for (size_t i = 0; i < wcslen(str); i++) {
        if (iswspace(str[i])) {
            flag = 0;
        } else {
            if (flag == 0) {
                count++;
                flag = 1;
            }
        }
    }
    return count;
}

int v_push_back(vector_t *v, wchar_t *el)
{
    if (v == NULL || el == NULL) {
        return -1;
    }

    if (v->size >= v->cap) {
        if (resize_vector(v) == -1) {
            return -1;
        }
    }

    size_t cp_size = wcslen(el) + 1;
    wchar_t *cp = malloc(cp_size * sizeof(wchar_t));
    if (cp == NULL) {
        return -1;
    }
    wcscpy(cp, el);
    v->elements[v->size].data = cp;
    v->elements[v->size].len = cp_size - 1;
    v->size++;
    return 0;
}

int v_remove_at(vector_t *v, size_t idx)
{
    if (v == NULL || idx >= v->size)
        return -1;

    free(v->elements[idx].data);
    for (size_t i = idx; i < v->size - 1; i++) {
        v->elements[i] = v->elements[i + 1];
    }
    v->size--;
    return 0;
}

int v_replace_at(vector_t *v, size_t idx, wchar_t *new_el)
{
    if (v == NULL || idx >= v->size || new_el == NULL) {
        return -1;
    }

    free(v->elements[idx].data);
    v->elements[idx].data = new_el;
    v->elements[idx].len = wcslen(new_el);

    return 0;
}