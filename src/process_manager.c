#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alphabet.h"
#include "error.h"
#include "string_util.h"

#include "io.h"
#include "process_manager.h"
#include "task_first.h"
#include "task_five_map.h"
#include "task_four.h"
#include "task_second.h"
#include "task_third.h"

#define BUFFER_SIZE 1024

// 0
static int task_zero(void)
{
    vector_t *v = read_text();
    if (v == NULL) {
        ERR("failed to read buffer stdin");
        return -1;
    }

    print_v(v);
    delete_vector(v);
    return 0;
}

// 1
static int task_replace_vowels(void)
{
    vector_t *v = read_text();
    if (v == NULL) {
        ERR("failed to read buffer stdin");
        return -1;
    }

    for (size_t i = 0; i < v->size; i++) {
        replace_vowels(v->elements[i].data, "EN");
        replace_vowels(v->elements[i].data, "RU");
    }

    print_v(v);
    delete_vector(v);
    return 0;
}

// 2
static int task_remove_first_words(void)
{
    vector_t *v = read_text();
    if (v == NULL) {
        ERR("failed to read buffer stdin");
        return -1;
    }

    size_t i = 0;
    while (i < v->size) {
        delete_first_word(v->elements[i].data);
        if (v_el_size(v->elements[i].data) == 0) {
            v_remove_at(v, i);
        } else {
            i++;
        }
    }
    print_v(v);

    delete_vector(v);
    return 0;
}

// 3
static int task_sort_by_first_word()
{
    vector_t *v = read_text();
    if (v == NULL) {
        ERR("failed to read buffer stdin");
        return -1;
    }

    sort_by_first_word(v);
    print_v(v);

    delete_vector(v);
    return 0;
}

// 4
static int task_digit_replacer(void)
{
    wchar_t *split = calloc(BUFFER_SIZE, sizeof(wchar_t));
    if (split == NULL) {
        ERR("failed to allocate");
        return -1;
    }

    wint_t wc;
    size_t i = 0;
    while ((wc = fgetwc(stdin)) != WEOF && wc != L'\n') {
        if (i + 1 < BUFFER_SIZE)
            split[i++] = (wchar_t)wc;
    }
    split[i] = L'\0';

    vector_t *v = read_text();
    if (v == NULL) {
        ERR("failed to read buffer stdin");
        return -1;
    }
    digit_to_alpha(v, split);
    print_v(v);

    free(split);
    delete_vector(v);
    return 0;
}

// 5
static int task_count_and_ss(void)
{
    vector_t *v = read_text();
    if (v == NULL) {
        ERR("failed to read buffer stdin");
        return -1;
    }
    word_entry_list *list = word_list_init();

    if (list == NULL) {
        ERR("failed to initialize word list");
        delete_vector(v);
        return -1;
    }

    for (size_t i = 0; i < v->size; i++) {
        if (e_read_sentence(v->elements[i].data, i, list) == -1) {
            ERR("failed to read a sentence");
        }
    }
    e_list_sort_by_f_letter(list);
    print_entry_list(list);

    free_word_list(list);
    delete_vector(v);
    return 0;
}

// 6 io.c

int run_process()
{
    int n;
    if (wscanf(L"%d", &n) != 1) {
        ERR("failed to read the number of task");
        return 0;
    }

    wint_t wc;
    while ((wc = getwchar()) != L'\n' && wc != WEOF)
        ;

    switch (n) {
        case 0:
            task_zero();
            break;
        case 1:
            task_replace_vowels();
            break;
        case 2:
            task_remove_first_words();
            break;
        case 3:
            task_sort_by_first_word();
            break;
        case 4:
            task_digit_replacer();
            break;
        case 5:
            task_count_and_ss();
            break;
        case 6:
            print_help();
            break;
        default:
            ERR("Failed to get the number, try to write numbers from 0 to 6");
            break;
    }

    return 0;
}
