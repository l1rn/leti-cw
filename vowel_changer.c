#include <string.h>
#include <stdio.h>
#include <wchar.h>
#include "vowel_changer.h"
#include "error.h"
#include "alphabet.h"
#include "string_util.h"

int find_and_replace(wchar_t *wc_s, int idx, const wchar_t al[], size_t al_size){
	if(wc_s == NULL){
		return -1;
	}
	for(size_t j = 0; j < al_size; j++){
		if(wc_s[idx] == al[j]){
			if(j + 1 >= al_size){
				wc_s[idx] = al[0];
				break;
			}
			else{
				wc_s[idx] = al[j + 1];
				break;
			}
		}
	}	

	return 0;
}

void replace_vowels(wchar_t *s, char al_sig[2]){
	if(s == NULL){
		return;
	}

	for(size_t i = 0; i < wcslen(s); i++){
		if(strcmp(al_sig, "EN") == 0){
			if(wmemchr(EN_VOWELS, s[i], EN_VOW_SIZE) != NULL){
				find_and_replace(s, i, EN_LOWER, EN_L_SIZE);
			}
		} 
		else if(strcmp(al_sig, "RU") == 0){
			if(wmemchr(RU_VOWELS, s[i], RU_VOW_SIZE) != NULL){
				find_and_replace(s, i, RU_LOWER, RU_L_SIZE);
			}
		}
	}
}
