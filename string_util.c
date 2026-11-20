#include "string_util.h"
#include <stdlib.h>

vector_t *create_vector(void){
	vector_t *v = malloc(sizeof(vector_t));
	iv(v == NULL){
		return NULL
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
