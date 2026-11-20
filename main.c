#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "delete_first_word.h"

int main(void){
	char *buf = malloc(200);
	if(buf == NULL){
		return 0;
	}
	if(fgets(buf, 200, stdin) == NULL){
		printf("Failed to read string.\n");
		free(buf);
		return 0;
	}
	buf[strcspn(buf, "\n")] = '\0';
	
	split_sentences_into_array(buf);
	delete_first_word(buf);

	printf("%s\n", buf);
	free(buf);

	return 0;
}
