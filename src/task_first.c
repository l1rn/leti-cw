#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

#include "alphabet.h"
#include "error.h"
#include "string_util.h"
#include "task_first.h"

wchar_t get_was_upper(wchar_t c, int was_upper)
{
    if (was_upper) {
        return towupper(c);
    }
    return c;
}

int find_and_replace(wchar_t *wc_s, int idx, const wchar_t al[], size_t al_size)
{
    if (wc_s == NULL) {
        return -1;
    }

    int was_upper = iswupper(wc_s[idx]);
    for (size_t j = 0; j < al_size; j++) {
        if (towlower(wc_s[idx]) == (wint_t)al[j]) {
            if (j + 1 >= al_size) {
                wc_s[idx] = get_was_upper(al[0], was_upper);
                break;
            } else {
                wc_s[idx] = get_was_upper(al[j + 1], was_upper);
                break;
            }
        }
    }

    return 0;
}

void replace_vowels(wchar_t *s, char al_sig[2])
{
    if (s == NULL) {
        return;
    }

    for (size_t i = 0; i < wcslen(s); i++) {
        if (strcmp(al_sig, "EN") == 0) {
            if (wmemchr(EN_VOWELS, towlower(s[i]), EN_VOW_SIZE) != NULL) {
                find_and_replace(s, i, EN_LOWER, EN_L_SIZE);
            }
        } else if (strcmp(al_sig, "RU") == 0) {
            if (wmemchr(RU_VOWELS, towlower(s[i]), RU_VOW_SIZE) != NULL) {
                find_and_replace(s, i, RU_LOWER, RU_L_SIZE);
            }
        }
    }
}
