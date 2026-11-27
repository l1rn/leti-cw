#include "task_four.h"
#include "error.h"
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

int digit_to_alpha(vector_t *v, wchar_t *word)
{
    if (v == NULL || word == NULL) {
        return -1;
    }

    size_t word_len = wcslen(word);
    for (size_t i = 0; i < v->size; i++) {
        wchar_t *old = v->elements[i].data;
        size_t old_len = v->elements[i].len;

        size_t digits = 0;
        for (size_t k = 0; k < old_len; k++) {
            if (iswdigit(old[k]))
                digits++;
        }

        size_t new_len = old_len - digits + (digits * word_len) + 1;
        wchar_t *res = malloc(new_len * sizeof(wchar_t));
        if (res == NULL) {
            ERR("failed to allocate memory");
            return -1;
        }

        size_t w = 0;
        for (size_t r = 0; r < old_len; r++) {
            if (iswdigit(old[r])) {
                wmemcpy(res + w, word, word_len);
                w += word_len;
            } else {
                res[w++] = old[r];
            }
        }
        res[w] = L'\0';

        size_t skip = 0;
        while (iswspace(res[skip]))
            skip++;
        if (skip > 0)
            wmemmove(res, res + skip, wcslen(res + skip) + 1);
        if (v_replace_at(v, i, res) == -1) {
            free(res);
            return -1;
        }
    }
    return 0;
}
