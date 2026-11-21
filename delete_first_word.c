#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <wchar.h>
#include "delete_first_word.h"
#include "string_util.h"
#include "error.h"

void delete_first_word(wchar_t *orig){
	wchar_t *space = wcschr(orig, ' ');
	if(space != NULL){
		wmemmove(orig, space + 1, wcslen(space + 1) + 1);
	} else{
		orig[0] = L'\0';
	}
}

void split_sentences_into_vector(vector_t *v, char *buf){
	wchar_t *wc_buf = get_wc(buf);
	wchar_t *buffer;

	wchar_t *token = wcstok(wc_buf, L".!?", &buffer);
	while(token != NULL){
		while(*token == ' ')
			token++;

		if(*token != L'\0'){
			
			int res = v_push_back(v, token);	
			if(res == -1){
				ERR("Error: failed to push sentence in vector");
				break;
			}
		}
		token = wcstok(NULL, L".!?", &buffer);
	}
	free_wc_string(wc_buf);
}
