#include "delete_first_word.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

void delete_first_word(char *orig){
	char *space = strchr(orig, ' ');
	if(space != NULL){
		memmove(orig, space + 1, strlen(space + 1) + 1);
	} else{
		orig[0] = '\0';
	}
	printf("orig: %s\n", orig);
}

void split_sentences_into_array(char *buf){
	char *token = strtok(buf, ".");
	while(token != NULL){
		while(*token == ' ')
			token++;
		printf("%s\n", token);
		token = strtok(NULL, ".");
	}
}
