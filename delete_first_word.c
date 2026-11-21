#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "delete_first_word.h"
#include "error.h"

void delete_first_word(char *orig){
	char *space = strchr(orig, ' ');
	if(space != NULL){
		memmove(orig, space + 1, strlen(space + 1) + 1);
	} else{
		orig[0] = '\0';
	}
}

void split_sentences_into_vector(vector_t *v, char *buf){
	char *cp = strdup(buf);
	if(!cp){
		ERR("Error: failed to copy buf");
		return;
	}
	char *token = strtok(cp, ".");
	while(token != NULL){
		while(*token == ' ')
			token++;

		if(*token != '\0'){
			size_t len = strlen(token);
			char *sentence = malloc(len + 2);
			if(sentence == NULL){
				ERR("failed to allocate a sentence");
				break;
			}
			// save a sign that was before '!' '.' '?'
			memcpy(sentence, token, len);
			sentence[len] = '.';
			sentence[len + 1] = '\0';

			int res = v_push_back(v, sentence);	
			free(sentence);
			if(res == -1){
				ERR("Error: failed to push sentence in vector");
				break;
			}
		}
		token = strtok(NULL, ".");
	}
	free(cp);
}
