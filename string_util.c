#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include "string_util.h"
#include "delete_first_word.h"
#include "error.h"

#define BUFFER_SIZE 1024

wchar_t *get_wc(char *c){
	if(c == NULL)
		return NULL;

	size_t c_size = mbstowcs(NULL, c, 0);
	if(c_size == (size_t) - 1){
		return NULL;
	}

	size_t slots = c_size + 1;
	wchar_t *wc = malloc(slots * sizeof(wchar_t));
	if(wc == NULL){
		return NULL;
	}

	size_t n = mbstowcs(wc, c, slots);
	if(n == (size_t) - 1){
		free(wc);
		return NULL;
	}
	return wc;
}

int is_terminator(wchar_t wc){
	return wc == L'.' || wc == L'!' || wc == L'?';
}

void split_sentences_into_vector(vector_t *v, wchar_t *wc_buf){
	size_t start = 0;
	while(wc_buf[start] != L'\0'){
		while(iswspace(wc_buf[start])){
			start++;
		}
		if(wc_buf[start] == L'\0'){
			break;
		}
		
		size_t end = start + wcscspn(wc_buf + start, L".!?");
		if(wc_buf[end] == L'\0'){
			break;
		}
		if(is_terminator(wc_buf[end])){
			size_t len = end - start + 1;
			wchar_t *cp = malloc((len + 1) * sizeof(wchar_t));
			if(cp == NULL){
				ERR("failed to allocate for a sentence");
				return;
			}
			wmemcpy(cp, wc_buf + start, len);
			cp[len] = L'\0';
			v_push_back(v, cp);
		}
		start = end + 1;
	}
}

void free_wc_string(wchar_t *wc_s){
	free(wc_s);
}

vector_t *create_vector(void){
	vector_t *v = malloc(sizeof(vector_t));
	if(v == NULL){
		return NULL;
	}
	v->size = 0;
	v->cap = 4;
	v->elements = malloc(v->cap * sizeof(wchar_t *));
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
	wchar_t **tmp = realloc(v->elements, new_cap * sizeof(wchar_t *));

	if(tmp == NULL){
		return -1;
	}
	v->elements = tmp;
	v->cap = new_cap;
	return 0;
}

int v_s_lower_cmp(wchar_t *s1, wchar_t *s2){
	wchar_t *cp1 = wcsdup(s1);
	wchar_t *cp2 = wcsdup(s2);
	for(size_t i = 0; i < wcslen(cp1); i++){
		cp1[i] = towlower(cp1[i]);
		cp2[i] = towlower(cp2[i]);
	}
	int res = wcscmp(cp1, cp2);
	free(cp1);
	free(cp2);
	return res;
}

int v_in_vector(vector_t *v, wchar_t *s){
	for(size_t i = 0; i < v->size; i++){
		if(wcslen(v->elements[i]) == wcslen(s)){
			return v_s_lower_cmp(v->elements[i], s);
		}
	}
	return -1;
}

int v_el_size(wchar_t *str){
	if(str == NULL){
		return -1;
	}

	int count = 0;
	int flag = 0;
	for(size_t i = 0; i < wcslen(str); i++){
		if(iswspace(str[i])){
			flag = 0;
		}
		else {
			if(flag == 0){
				count++;
				flag = 1;
			}
		}
	}
	return count;
}

int v_push_back(vector_t *v, wchar_t *el){
	if(v == NULL || el == NULL){
		return -1;
	}

	if(v->size >= v->cap){
		if(resize_vector(v) == -1){
			return -1;
		}
	}

	size_t cp_size = wcslen(el) + 1;
	wchar_t *cp = malloc(cp_size * sizeof(wchar_t));
	if(cp == NULL){
		return -1;
	}
	wcscpy(cp, el);
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

int v_replace_at(vector_t *v, size_t idx, wchar_t *new_el){
	if(v == NULL || idx >= v->size || new_el == NULL){
		return -1;
	}

	free(v->elements[idx]); 
	v->elements[idx] = new_el;

	return 0;
}

void print_v(vector_t *v){
	for(size_t i = 0; i < v->size; i++){
		wprintf(L"%ls\n", v->elements[i]);
	}
}

int check_for_end_sentence(wint_t wc, int flag){
	return flag == 1 && (wchar_t)wc == L'\n';
}

vector_t *read_sentences(void){
	size_t cap = BUFFER_SIZE;
	wchar_t *buf = malloc(cap * sizeof(wchar_t));
	size_t size = 0;

	if(buf == NULL){
		return NULL;
	}

	wint_t wc;
	int flag_was_end = 0;
	while((wc = fgetwc(stdin)) != WEOF) {
		if(size + 1 >= cap){
			size_t new_cap = cap * 2;
			wchar_t *tmp = realloc(buf, new_cap * sizeof(wchar_t));
			if(tmp == NULL){
				free(buf);
				return NULL;
			}
			buf = tmp;
			cap = new_cap;
		} 
		if(check_for_end_sentence(wc, flag_was_end)){
			if(size > 0) size--;
			break;
		}
		if(wc == L'\n') {
			flag_was_end = 1;
			buf[size++] = L' ';
		}
		else{
			flag_was_end = 0;
			buf[size++] = (wchar_t)wc;
		}
	}
	buf[size] = L'\0';

	vector_t *v = create_vector();

	if(v != NULL){
		split_sentences_into_vector(v, buf);
	}

	free(buf);
	return v;
}
