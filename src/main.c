#include "process_manager.h"
#include <locale.h>
#include <stdio.h>
#include <wchar.h>

int main(void)
{
    setlocale(LC_ALL, "");
    wprintf(L"Course work for option 5.1, created by Ivan Taksatov.\n");
    run_process();
    return 0;
}
