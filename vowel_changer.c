#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "vowel_changer.h"
#include "alphabet.h"

wchar_t *get_wc(const char *c){
	const size_t c_size = strlen(c) + 1;
	wchar_t *wc = malloc(c_size * sizeof(wchar_t *));
	if(wc == NULL){
		return NULL;
	}
	size_t res = mbstowcs(wc, c, c_size);
	if(res == c_size - 1){
		return NULL;
	}
	return wc;
}

wchar_t *get_wc_string(char *s){
	wchar_t *wc_s = malloc((sizeof(wchar_t) * strlen(s)) + sizeof(wchar_t));	
	if(wc_s == NULL){
		return NULL;
	}
	for(size_t i = 0; i < strlen(s); i++){
		wc_s[i] = get_wc(s[i]);
	}
	wc_s[wcslen(wc_s)] = L'\0';
	return wc_s;
}

void free_wc_string(wchar_t *wc_s){
	for(size_t i = 0; i < wcslen(wc_s); i++){
		free(wc_s[i]);
	}
	free(wc_s[i]);
}

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

void replace_vowels(char *s, char al_sig[2]){
	if(s == NULL){
		return;
	}

	wchar_t *wc_s = get_wc_string(s);
	if(wc_s == NULL){
		ERR("failed to allocate memory for wchar_t sentence");
		return;
	}

	for(size_t i = 0; i < strlen(s); i++){
		if(strcmp(al_sig, "EN") == 0){
			if(wmemchr(EN_VOWELS, s[i], EN_VOW_SIZE) != NULL){
				wprintf(L"%5lc\n", s[i]);
				find_and_replace(s, i, al_sig);
			}
		} 
		else if(strcmp(al_sig, "RU") == 0){
			wprintf("%c\n", s[i]);
			if(wmemchr(RU_VOWELS, s[i], RU_VOW_SIZE) != NULL){
				find_and_replace(s, i, al_sig);
			}
		}
	}
	free_wc_string(wc_s);
}
