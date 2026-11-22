#include "store_util.h"
#include <stdlib.h>
#include <wchar.h>

word_entry_t *create_word_entry(wchar_t *v){
	word_entry_t *e = malloc(sizeof(word_entry_t));
	if(e == NULL){
		return NULL;
	}

	e->size = 0;
	e->cap = 4;
	e->arr = malloc(sizeof(int) * e->cap);

	if(e->arr == NULL){
		free(e->arr);
		free(e);
		return NULL;
	}
	
	wchar_t *word = wcsdup(v);
	e->value = word;

	return e;
}

word_entry_t *find_entry(word_entry_t *entries, size_t n, wchar_t *word){
	for(size_t i = 0; i < n; i++)
		if(wcscmp(entries[i].value, word) == 0)
			return &entries[i];
	return NULL;
}

int e_push_back(word_entry_t *e, int idx){
	if(e->size == e->cap){
		int new_cap = e->cap * 2;
		int *tmp = realloc(e->arr, new_cap * sizeof(int));
		if(tmp == NULL){
			return -1;
		}
		e->arr = tmp;
		e->cap = new_cap;
	}
	e->arr[e->size++] = idx;
	return 0;
}

int e_read_sentence(wchar_t *s, word_entry_t *entries, size_t n){
	if(s == NULL){
		return -1;
	}
	wchar_t *buffer;
	wchar_t *token = wcstok(s, L" ,.!?", &buffer);
	size_t i = 0;
	while(token != NULL){
		word_entry_t *e = find_entry(entries, n, token);
		if(e == NULL){
			e = create_word_entry(word);
		} else {
			
		}
		token = wcstok(s, L" ,.!?", &buffer);
	}
	wprintf(L"%ls\n", token);
	return 0;
}

void free_word_entry(word_entry_t *e){
	free(e->value);
	free(e->arr);
}
