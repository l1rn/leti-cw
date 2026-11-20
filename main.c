#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "string_util.h"
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

	vector_t *v = create_vector();
	v_push_back(v, "sidfiadsfiadfidsa. 3 23 42");
	v_push_back(v, " fsafdsadsa dsa");
	print_v(v);
	delete_vector(v);

	printf("%s\n", buf);
	free(buf);

	return 0;
}
