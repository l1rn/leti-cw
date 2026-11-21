#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "vowel_changer.h"
#include "error.h"
#include "alphabet.h"
#include "string_util.h"

int find_and_replace(wchar_t *wc_s, int idx, char al_sig[2]){
	if(wc_s == NULL){
		return -1;
	}

	if(strcmp(al_sig, "RU") == 0){
		for(size_t j = 0; j < RU_L_SIZE; j++){
			if(wc_s[idx] == RU_LOWER[j]){
				if(j + 1 >= RU_L_SIZE){
					wc_s[idx] = RU_LOWER[0];
					break;
				}
				else{
					wc_s[idx] = RU_LOWER[j + 1];
					break;
				}
			}
		}	
	} 
	else if(strcmp(al_sig, "EN") == 0){
		for(size_t j = 0; j < EN_L_SIZE; j++){
			if(wc_s[idx] == EN_LOWER[j]){
				if(j + 1 >= EN_L_SIZE){
					wc_s[idx] = EN_LOWER[0];
					break;
				}
				else{
					wc_s[idx] = EN_LOWER[j + 1];
					break;
				}
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
				find_and_replace(s, i, al_sig);
			}
		} 
		else if(strcmp(al_sig, "RU") == 0){
			if(wmemchr(RU_VOWELS, s[i], RU_VOW_SIZE) != NULL){
				find_and_replace(s, i, al_sig);
			}
		}
	}
}
