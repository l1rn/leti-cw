#include "delete_first_word.h"
#include "error.h"
#include "string_util.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

void delete_first_word(wchar_t *s)
{
    size_t i = 0;
    while (s[i] != L'\0' && !iswalpha(s[i]))
        i++;

    while (iswalpha(s[i]))
        i++;

    while (s[i] != L'\0' && !iswalpha(s[i]))
        i++;

    if (s[i] == L'\0') {
        s[0] = L'\0';
        return;
    }
    wmemmove(s, s + i, wcslen(s + i) + 1);
}
