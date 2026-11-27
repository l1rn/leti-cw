#include "task_five_map.h"
#include "error.h"
#include "string_util.h"
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

word_entry_t *create_word_entry(wchar_t *v)
{
    if (v == NULL) {
        ERR("can't create a word entry because value is NULL");
        return NULL;
    }
    word_entry_t *e = malloc(sizeof(word_entry_t));
    if (e == NULL) {
        ERR("failed to allocate memory for word_entry");
        return NULL;
    }

    e->size = 0;
    e->cap = 4;
    e->count = 0;
    e->arr = malloc(e->cap * sizeof *e->arr);

    if (e->arr == NULL) {
        free(e->arr);
        free(e);
        ERR("failed to allocate for an array in word_entry");
        return NULL;
    }

    wchar_t *word = wcsdup(v);
    if (word == NULL) {
        free(e->arr);
        free(e);
        ERR("failed to duplicate a value");
        return NULL;
    }
    e->value = word;

    return e;
}

word_entry_list *word_list_init()
{
    word_entry_list *l = malloc(sizeof(word_entry_list));
    l->size = 0;
    l->cap = 8;
    l->items = malloc(l->cap * sizeof *l->items);
    if (l->items == NULL) {
        ERR("failed to allocate memory for l->items");
        return NULL;
    }
    return l;
}

word_entry_t *find_entry(word_entry_list *entries, wchar_t *word)
{
    for (size_t i = 0; i < entries->size; i++)
        if (wcscmp(entries->items[i]->value, word) == 0)
            return entries->items[i];
    return NULL;
}

int resize_word_list(word_entry_list *l)
{
    if (l->size >= l->cap) {
        size_t new_cap = l->cap ? l->cap * 2 : 4;
        word_entry_t **tmp = realloc(l->items, new_cap * sizeof *l->items);
        if (tmp == NULL) {
            return -1;
        }
        l->items = tmp;
        l->cap = new_cap;
    }

    return 0;
}

static int e_idx_is_duplicate(word_entry_t *e, int idx)
{
    for (size_t i = 0; i < e->size; i++) {
        if (e->arr[i] == idx) {
            return 1;
        }
    }
    return 0;
}

int e_push_back(word_entry_t *e, int idx)
{
    if (e == NULL) {
        return -1;
    }
    if (e_idx_is_duplicate(e, idx)) {
        e->count += 1;
        return 0;
    }

    if (e->size >= e->cap) {
        size_t new_cap = e->cap * 2;
        int *tmp = realloc(e->arr, new_cap * sizeof *e->arr);
        if (tmp == NULL) {
            return -1;
        }
        e->arr = tmp;
        e->cap = new_cap;
    }
    e->arr[e->size++] = idx;
    e->count += 1;
    return 0;
}

int e_push_back_list(word_entry_list *l, wchar_t *value, int idx)
{
    if (l == NULL || value == NULL) {
        return -1;
    }
    if (resize_word_list(l) == -1) {
        ERR("failed to resize word_entry_list");
        return -1;
    }

    for (size_t i = 0; i < l->size; i++) {
        if (wcscmp(l->items[i]->value, value) == 0) {
            e_push_back(l->items[i], idx);
            return 0;
        }
    }

    word_entry_t *e = create_word_entry(value);
    if (e == NULL) {
        ERR("failed to create an entry");
        return -1;
    }
    e_push_back(e, idx);

    l->items[l->size++] = e;
    return 0;
}

static wchar_t *e_to_lower(wchar_t *token)
{
    wchar_t *cp = wcsdup(token);
    for (size_t i = 0; i < wcslen(cp); i++) {
        cp[i] = towlower(cp[i]);
    }
    return cp;
}

int e_read_sentence(wchar_t *s, int idx, word_entry_list *entries)
{
    if (s == NULL) {
        ERR("vector->elements is empty")
        return -1;
    }

    wchar_t *buffer;
    wchar_t *token = wcstok(s, L" \"\',/\n\t;:.!?()[]{}&+|~<>", &buffer);
    while (token != NULL) {
        if (is_terminator(token[wcslen(token) - 1])) {
            token[wcslen(token) - 1] = L'\0';
        }
        wchar_t *token_lower = e_to_lower(token);
        if(e_push_back_list(entries, token_lower, idx) == -1){
            ERR("failed to push in an entry list");
            return -1;
        }
        free(token_lower);
        token = wcstok(NULL, L" \"\',/\n\t;:.!?()[]{}&+|~<>", &buffer);
    }
    return 0;
}

static int cmp_word(const void *a, const void *b)
{
    word_entry_t *pa = *(word_entry_t *const *)a;
    word_entry_t *pb = *(word_entry_t *const *)b;
    return wcscmp(pa->value, pb->value);
}

void e_list_sort_by_f_letter(word_entry_list *l)
{
    if (l == NULL || l->items == NULL || l->size == 0)
        return;
    qsort(l->items, l->size, sizeof(word_entry_t *), cmp_word);
}


void free_word_entry(word_entry_t *e)
{
    free(e->value);
    free(e->arr);
    free(e);
}

void free_word_list(word_entry_list *l)
{
    for (size_t i = 0; i < l->size; i++) {
        free_word_entry(l->items[i]);
    }
    free(l->items);
    free(l);
}
