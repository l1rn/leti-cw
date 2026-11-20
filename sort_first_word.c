#include "sort_first_word.h"
#include <stdlib.h>
#include <string.h>

int len_first_word(char *str){
	char *cp = strdup(str);
	char *t = strtok(cp, " ");
	int len = strlen(t);
	free(cp);
	return len;
}

int cmp_first_word(const void *a, const void *b){
	const char *s1 = *(char * const *)a;
	const char *s2 = *(char * const *)b;
	
	int s1_len = len_first_word(s1);
	int s2_len = len_first_word(s2);
	return s1_len > s2_len;
}

void sort_by_first_word(vector_t *v){
	if(v == NULL || v->size < 2){
		return;
	}
	qsort(v->elements, v->size, sizeof(char *), cmp_first_word);
}
