#include "delete_first_word.h"
#include "error.h"
#include "string_util.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

void delete_first_word(wchar_t *orig)
{
    wchar_t *space = wcschr(orig, ' ');
    if (space != NULL) {
        wmemmove(orig, space + 1, wcslen(space + 1) + 1);
    } else {
        orig[0] = L'\0';
    }
}
