#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "string_util.h"
#include "error.h"

vector_t *create_vector(void){
	vector_t *v = malloc(sizeof(vector_t));
	if(v == NULL){
		return NULL;
	}
	v->size = 0;
	v->cap = 4;
	v->elements = malloc(v->cap * sizeof(char *));
	if(v->elements == NULL){
		free(v);
		return NULL;
	}
	return v;
}

void delete_vector(vector_t *v){
	if(v == NULL){
		return;
	}
	for(size_t i = 0; i < v->size; i++){
		free(v->elements[i]);
	}
	free(v->elements);
	free(v);
}

int resize_vector(vector_t *v){
	int new_cap = v->cap * 2;
	char **tmp = realloc(v->elements, new_cap * sizeof(char *));

	if(tmp == NULL){
		return -1;
	}
	v->elements = tmp;
	v->cap = new_cap;
	return 0;
}

int v_el_size(char *str){
	char *cp = strdup(str);
	if(!cp){
		return 0;
	}
	int count = 0;
	char *t = strtok(cp, " ");
	while(t != NULL){
		count++;
		t = strtok(NULL, " ");
	}
	free(cp);
	return count;
}

int v_push_back(vector_t *v, char *el){
	if(v->size >= v->cap){
		if(resize_vector(v) == -1){
			return -1;
		}
	}

	char *cp = malloc(strlen(el) + 1);
	if(!cp){
		return -1;
	}
	strcpy(cp, el);
	v->elements[v->size++] = cp;
	return 0;
}

int v_remove_at(vector_t *v, size_t idx){
	if(v == NULL || idx >= v->size)
		return -1;

	free(v->elements[idx]);
	for(size_t i = idx; i < v->size - 1; i++){
		v->elements[i] = v->elements[i + 1];
	}
	v->size--;
	return 0;
}

void print_v(vector_t *v){
	for(size_t i = 0; i < v->size; i++){
		printf("%s (%d)\n", v->elements[i], v_el_size(v->elements[i]));
	}
}

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
