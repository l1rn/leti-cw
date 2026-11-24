#include "task_manager.h"
#include <locale.h>
#include <stdio.h>
#include <wchar.h>

int main(void)
{
    setlocale(LC_ALL, "");
    wprintf(L"Course work for option \e[1;94m4.1\e[0;0m, created by \e[1;95mIvan Taksatov\e[0;0m\n");
    run_process();
    return 0;
}
