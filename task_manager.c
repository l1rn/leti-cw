#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alphabet.h"
#include "string_util.h"
#include "task_manager.h"
#include "delete_first_word.h"
#include "sort_first_word.h"
#include "error.h"
#include "vowel_changer.h"

//1
static int task_replace_vowels(void){
	vector_t *v = read_sentences();
	if(v == NULL)
		return -1;
	
	size_t i = 0;
	while(i < v->size){
		// todo: for capital letters shift their value
		replace_vowels(v->elements[i], "EN");	

		replace_vowels(v->elements[i], "RU");	
		i++;
	}
	print_v(v);
	return 0;
}

// 2
static int task_remove_first_words(void){
	vector_t *v = read_sentences();
	if(v == NULL)
		return -1;

	size_t i = 0;
	while(i < v->size){
		delete_first_word(v->elements[i]);
		if(v_el_size(v->elements[i]) == 0){
			v_remove_at(v, i);			
		} else{
			i++;
		}
	}
	print_v(v);

	delete_vector(v);
	return 0;
}

// 3
static int task_sort_by_first_word(){
	vector_t *v = read_sentences();
	if(v == NULL)
		return -1;

	sort_by_first_word(v);
	print_v(v);

	delete_vector(v);
	return 0;
}

int run_process(){
	int n;
	if(scanf("%d", &n) != 1){
		ERR("Failed to read the number of task");
		return 0;
	}
	int c;
	while((c = getchar()) != '\n' && c != EOF);

	switch(n){
		case 0:
			break;
		case 1:
			task_replace_vowels();
			break;
		case 2: 
			task_remove_first_words();
			break;
		case 3:
			task_sort_by_first_word();
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		default:
			ERR("Failed to get the number, try to write numbers from 0 to 6");
			break;
	}
		
	return 0;
}
