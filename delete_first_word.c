#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "delete_first_word.h"

void delete_first_word(char *orig){
	char *space = strchr(orig, ' ');
	if(space != NULL){
		memmove(orig, space + 1, strlen(space + 1) + 1);
	} else{
		orig[0] = '\0';
	}
	printf("orig: %s\n", orig);
}

void split_sentences_into_vector(vector_t *v, char *buf){
	char *cp = strdup(buf);
	if(!cp){
		printf("Error: failed to copy buf");
		return;
	}
	char *token = strtok(cp, ".");
	while(token != NULL){
		while(*token == ' ')
			token++;

		if(*token != '\0'){
			if(v_push_back(v, token) == -1){
				printf("Error: failed to push sentence in vector");
			}
		}
		token = strtok(NULL, ".");
	}
}
