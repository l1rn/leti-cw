#include "io.h"
#include "error.h"
#include "task_five_map.h"

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#define BUFFER_SIZE 1024

static int v_is_duplicate(vector_t *v, wchar_t *s)
{
    size_t size_ws = wcslen(s);
    for (size_t i = 0; i < v->size; i++) {
        if (v_s_lower_cmp(v->elements[i].data, s, size_ws)) {
            return 1;
        }
    }
    return 0;
}

static int check_for_end_sentence(wint_t wc, int flag)
{
    return flag == 1 && (wchar_t)wc == L'\n';
}

void split_sentences_into_vector(vector_t *v, wchar_t *wc_buf)
{
    size_t start = 0;
    while (wc_buf[start] != L'\0') {
        while (iswspace(wc_buf[start])) {
            start++;
        }
        if (wc_buf[start] == L'\0') {
            break;
        }

        size_t end = start + wcscspn(wc_buf + start, L".!?");
        if (wc_buf[end] == L'\0') {
            break;
        }
        if (is_terminator(wc_buf[end])) {
            size_t len = end - start + 1;
            wchar_t *cp = malloc((len + 1) * sizeof(wchar_t));
            if (cp == NULL) {
                ERR("failed to allocate memory for a sentence");
                return;
            }
            wmemcpy(cp, wc_buf + start, len);
            cp[len] = L'\0';
            if (!v_is_duplicate(v, cp)) {
                if (v_push_back(v, cp) == -1) {
                    free(cp);
                    ERR("failed to push a sentence");
                    return;
                }
            }

            free(cp);
        }
        start = end + 1;
    }
}

vector_t *read_text(void)
{
    size_t cap = BUFFER_SIZE;
    wchar_t *buf = malloc(cap * sizeof(wchar_t));
    size_t size = 0;

    if (buf == NULL) {
        return NULL;
    }

    wint_t wc;
    int flag_was_end = 0;
    while ((wc = fgetwc(stdin)) != WEOF) {
        if (size + 1 >= cap) {
            size_t new_cap = cap * 2;
            wchar_t *tmp = realloc(buf, new_cap * sizeof(wchar_t));
            if (tmp == NULL) {
                free(buf);
                return NULL;
            }
            buf = tmp;
            cap = new_cap;
        }
        if (check_for_end_sentence(wc, flag_was_end)) {
            if (size > 0)
                size--;
            break;
        }
        if (wc == L'\n') {
            flag_was_end = 1;
            buf[size++] = L' ';
        } else {
            flag_was_end = 0;
            buf[size++] = (wchar_t)wc;
        }
    }
    buf[size] = L'\0';

    vector_t *v = create_vector();

    if (v != NULL) {
        split_sentences_into_vector(v, buf);
    }

    free(buf);
    return v;
}

void print_v(vector_t *v)
{
    for (size_t i = 0; i < v->size; i++) {
        wprintf(L"%ls\n", v->elements[i].data);
    }
}

void print_entry_list(word_entry_list *ens)
{
    if (ens == NULL) {
        wprintf(L"ens is null!\n");
    }

    for (size_t i = 0; i < ens->size; i++) {
        wprintf(L"%ls: %d; sentences=", ens->items[i]->value, ens->items[i]->count);
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

void print_help(void)
{
    wprintf(L"0 - Вывод текста после первичной обработки.\n");
    wprintf(L"1 - Замена гласных следующей буквой алфавита.\n");
    wprintf(L"2 - Удаление первого слова в каждом предложении.\n");
    wprintf(L"3 - Сортировка предложений по длине первого слова.\n");
    wprintf(L"4 - Замена каждой цифры введённой строкой.\n");
    wprintf(L"5 - Подсчёт слов и номера предложений, где они встречаются.\n");
    wprintf(L"6 - Вывод справки.\n");
}