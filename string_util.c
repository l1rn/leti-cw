#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "string_util.h"

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

void print_v(vector_t *v){
	for(size_t i = 0; i < v->size; i++){
		printf("%s\n", v->elements[i]);
	}
}
