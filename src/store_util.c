#include "store_util.h"
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

static int is_terminator(wchar_t wc){
	return wc == L'!' || wc == L'?' || wc == L'.';
}

int e_read_sentence(wchar_t *s, int idx, word_entry_list *entries)
{
    if (s == NULL) {
        return -1;
    }

    wchar_t *buffer;
    wchar_t *token = wcstok(s, L" \"\',/\n\t;:.!?()[]{}&+|~<>", &buffer);
    while (token != NULL) {
        if (is_terminator(token[wcslen(token) - 1])) {
            token[wcslen(token) - 1] = L'\0';
        }
        wchar_t *token_lower = e_to_lower(token);
        e_push_back_list(entries, token_lower, idx);
        free(token_lower);
        token = wcstok(NULL, L" \"\',/\n\t;:.!?()[]{}&+|~<>", &buffer);
    }
    return 0;
}

int cmp_first_letter(const void *a, const void *b){
	word_entry_t *pa = *(word_entry_t *const *)a;
	wchar_t x = pa->value[0];
	word_entry_t *pb = *(word_entry_t *const *)b;
	wchar_t y = pb->value[0];
	
	if(x > y){
		return 1;
	}
	if(x < y){
		return -1;
	}
	return 0;
}

void e_list_sort_by_f_letter(word_entry_list *l){
	if(l == NULL || l->items == NULL || l->size == 0) return;
	qsort(l->items, l->size, sizeof(word_entry_t *), cmp_first_letter);
}

void print_entry_list(word_entry_list *ens)
{
    if (ens == NULL) {
        wprintf(L"ens is null!\n");
    }

    for (size_t i = 0; i < ens->size; i++) {
        wprintf(L"%ls: %zu; sentences=", ens->items[i]->value, ens->items[i]->size);
        for (size_t j = 0; j < ens->items[i]->size; j++) {
            if (j + 1 == ens->items[i]->size) {
                wprintf(L"%zu", ens->items[i]->arr[j] + 1);
            } else {
                wprintf(L"%zu,", ens->items[i]->arr[j] + 1);
            }
        }
        wprintf(L"\n");
    }
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
