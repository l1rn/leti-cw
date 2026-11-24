#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alphabet.h"
#include "delete_first_word.h"
#include "digit_to_alpha.h"
#include "error.h"
#include "sort_first_word.h"
#include "store_util.h"
#include "string_util.h"
#include "task_manager.h"
#include "vowel_changer.h"

// 0
static int task_zero(void)
{
    vector_t *v = read_sentences();
    if (v == NULL) {
        return -1;
    }

    print_v(v);
    delete_vector(v);
    return 0;
}

// 1
static int task_replace_vowels(void)
{
    vector_t *v = read_sentences();
    if (v == NULL)
        return -1;

    for (size_t i = 0; i < v->size; i++) {
        replace_vowels(v->elements[i], "EN");
        replace_vowels(v->elements[i], "RU");
    }

    print_v(v);
    delete_vector(v);
    return 0;
}

// 2
static int task_remove_first_words(void)
{
    vector_t *v = read_sentences();
    if (v == NULL)
        return -1;

    size_t i = 0;
    while (i < v->size) {
        delete_first_word(v->elements[i]);
        if (v_el_size(v->elements[i]) == 0) {
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
    vector_t *v = read_sentences();
    if (v == NULL)
        return -1;

    sort_by_first_word(v);
    print_v(v);

    delete_vector(v);
    return 0;
}

// 4
static int task_digit_replacer(void)
{
    wchar_t *split = malloc(256 * sizeof(wchar_t));

    wscanf(L"%256ls", split);
    if (split == NULL) {
        ERR("failed to read split");
        return -1;
    }

    vector_t *v = read_sentences();
    for (size_t i = 0; i < v->size; i++) {
        v_replace_at(v, i, digit_to_alpha(v->elements[i], split));
        i++;
    }
    print_v(v);

    free(split);
    delete_vector(v);
    return 0;
}

// 5
static int task_count_and_ss(void)
{
    vector_t *v = read_sentences();
    word_entry_list list;

    if (word_list_init(&list) == -1) {
        delete_vector(v);
        return -1;
    }

    for (size_t i = 0; i < v->size; i++) {
        e_read_sentence(v->elements[i], i, &list);
    }

    free_word_list(&list);
    delete_vector(v);
    return 0;
}

// 6
void print_help(void)
{
    wprintf(L"0 - Вывод текста после первичной обработки (удаление повторяющихся предложений без учёта "
            L"регистра).\n"
            L"1 - Замена гласных следующей буквой алфавита с сохранением регистра.\n"
            L"    Английские гласные: aeiou.\n"
            L"    Полученные буквы повторно не заменяются.\n"
            L"2 - Удаление первого слова в каждом предложении вместе с разделителями\n"
            L"    до второго слова (весь фрагмент от начала предложения до начала\n"
            L"    второго слова). Остальная часть предложения сохраняется.\n"
            L"    Если слов не осталось, предложение удаляется.\n"
            L"3 - Сортировка предложений по возрастанию длины первого слова.\n"
            L"    При равных длинах сохраняется исходный порядок предложений.\n"
            L"    Для предложения без слов ключ сортировки равен 0.\n"
            L"    Если во всём тексте нет предложений со словами, выводится текст\n"
            L"    после первичной обработки без изменения порядка предложений.\n"
            L"4 - Замена каждой цифры строкой, введённой отдельной строкой сразу\n"
            L"    после номера команды и перед основным текстом.\n"
            L"    Строка замены может быть пустой и иметь любую длину.\n"
            L"    Цифры внутри слов тоже заменяются.\n"
            L"    Вставленная строка повторно не обрабатывается.\n"
            L"    Начальные пробельные символы получившихся предложений удаляются,\n"
            L"    остальные разделители сохраняются.\n"
            L"5 - в процессе.\n");
}

int run_process()
{
    int n;
    if (wscanf(L"%d", &n) != 1) {
        ERR("failed to read the number of task");
        return 0;
    }
    int c;
    while ((c = getwchar()) != '\n' && c != EOF)
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
