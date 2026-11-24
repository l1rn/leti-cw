#include "store_util.h"
#include "error.h"
#include <stdlib.h>
#include <wchar.h>

word_entry_t *create_word_entry(wchar_t *v)
{
    word_entry_t *e = malloc(sizeof(word_entry_t));
    if (e == NULL) {
        return NULL;
    }

    e->size = 0;
    e->cap = 4;
    e->arr = malloc(sizeof(int) * e->cap);

    if (e->arr == NULL) {
        free(e->arr);
        free(e);
        return NULL;
    }

    wchar_t *word = wcsdup(v);
    e->value = word;

    return e;
}

int word_list_init(word_entry_list *l)
{
    l->size = 0;
    l->cap = 8;
    l->items = malloc(l->cap * sizeof *l->items);
    if (l->items == NULL) {
        ERR("failed to allocate memory for l->items");
        return -1;
    }
    return 0;
}

word_entry_t *find_entry(word_entry_list *entries, wchar_t *word)
{
    for (size_t i = 0; i < entries->size; i++)
        if (wcscmp(entries->items[i].value, word) == 0)
            return &entries->items[i];
    return NULL;
}

int word_list_add_item(word_entry_list *l, word_entry_t *e)
{
    if (l == NULL || e == NULL) {
        ERR("null list or word_entry");
        return -1;
    }

    if (l->size >= l->cap) {
        size_t new_cap = l->cap ? l->cap * 2 : 4;
        word_entry_t *tmp = realloc(l->items, new_cap * sizeof *tmp);
        if (tmp == NULL) {
            return -1;
        }
        l->items = tmp;
        l->cap = new_cap;
    }

    l->items[l->size++] = *e;
    return 0;
}

int word_list_find_or_add_item(word_entry_list *l, wchar_t *value)
{
    if (find_entry(l, value) != NULL)
        return 1;
    else {
        if (word_list_add_item(l, find_entry(l, value)) != -1)
            return 0;
    }
    return -1;
}

int e_push_back(word_entry_t *e, int idx)
{
    if (e->size == e->cap) {
        int new_cap = e->cap * 2;
        int *tmp = realloc(e->arr, new_cap * sizeof(int));
        if (tmp == NULL) {
            return -1;
        }
        e->arr = tmp;
        e->cap = new_cap;
    }
    e->arr[e->size++] = idx;
    return 0;
}

int e_read_sentence(wchar_t *s, int idx, word_entry_list *entries)
{
    if (s == NULL) {
        return -1;
    }

    wchar_t *buffer;
    wchar_t *token = wcstok(s, L" ,;", &buffer);
    while (token != NULL) {
        word_entry_t *e = find_entry(entries, token);
        if (e == NULL) {
            e = create_word_entry(token);
        } else {
            e_push_back(e, idx);
        }
        token = wcstok(s, L" ,;", &buffer);
    }
    wprintf(L"%ls\n", token);
    return 0;
}

void free_word_entry(word_entry_t *e)
{
    free(e->value);
    free(e->arr);
}

void free_word_list(word_entry_list *l)
{
    for (size_t i = 0; i < l->size; i++) {
        free_word_entry(&l->items[i]);
    }
    free(l->items);
    l->items = NULL;
    l->size = l->cap = 0;
}
