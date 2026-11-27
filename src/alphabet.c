#include "alphabet.h"

#define SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

const wchar_t EN_LOWER[] = L"abcdefghijklmnopqrstuvwxyz";
const wchar_t EN_VOWELS[] = L"aeiou";

const wchar_t RU_LOWER[] = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
const wchar_t RU_VOWELS[] = L"аеёиоуыэюя";

const size_t EN_L_SIZE = SIZE(EN_LOWER) - 1;
const size_t EN_VOW_SIZE = SIZE(EN_VOWELS) - 1;

const size_t RU_L_SIZE = SIZE(RU_LOWER) - 1;
const size_t RU_VOW_SIZE = SIZE(RU_VOWELS) - 1;

const wchar_t SPECIAL_SIGNS[] = {L'@', L'$', L'#', L'№', L'%', L'^', L'*', L'_', L'-'};
const size_t SPECIAL_SIGNS_SIZE = SIZE(SPECIAL_SIGNS);
