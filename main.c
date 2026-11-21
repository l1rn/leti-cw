#include "task_manager.h"
#include <stdio.h>
#include <locale.h>

int main(void){
	setlocale(LC_ALL, "");
	printf("Course work for option \e[1;94m1\e[0;37m, created by \e[1;95mIvan Taksatov\e[0;0m\n");
	run_process();
	return 0;
}
