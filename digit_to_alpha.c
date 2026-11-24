#include "digit_to_alpha.h"
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

wchar_t *digit_to_alpha(wchar_t *s, wchar_t *r)
{
    if (s == NULL || r == NULL) {
        return NULL;
    }

    size_t size = wcslen(s);
    size_t size_r = wcslen(r);
    size_t count = 0;
    for (size_t j = 0; j < size; j++) {
        if (iswdigit(s[j]))
            count++;
    }

    size_t res_len = size - count + count * size_r + 1;
    wchar_t *res = malloc(res_len * sizeof(wchar_t));
    if (res == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < size; i++) {
        if (iswdigit(s[i])) {
            wmemcpy(res + j, r, size_r);
            j += size_r;
        } else {
            res[j] = s[i];
            j++;
        }
    }
    res[j] = L'\0';

    return res;
}
