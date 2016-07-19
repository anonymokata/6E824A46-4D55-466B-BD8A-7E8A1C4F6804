#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include "roman.h"

/**
Contracting Roman Numerals.
IIII -> IV
VIIII -> IX
XXXX -> XL
LXXXX -> XC
CCCC -> CD
DCCCC -> CM
**/

void replace_string_with_smaller_string_in(char *text, char *longer_string,
                                           char *shorter_string) {
  size_t length_text = strlen(text);
  assert(length_text > 0);
  size_t length_longer_string = strlen(longer_string);
  assert(length_longer_string > 0);
  size_t length_shorter_string = strlen(shorter_string);
  assert(length_shorter_string > 0);
  assert(length_shorter_string < length_longer_string);
  if (length_text >= length_longer_string) {
    char *first_entry = strstr(text, longer_string);
    while (first_entry != NULL) {
      memcpy(first_entry, shorter_string, length_shorter_string);
      memmove(&first_entry[length_shorter_string],
              &first_entry[length_longer_string],
              strlen(&first_entry[length_longer_string]));
      length_text -= length_longer_string - length_shorter_string;
      text[length_text] = '\0';
      first_entry = strstr(text, longer_string);
    }
  }
}

void normalize_roman_numeral_string(char *roman_numeral_string) {
  replace_string_with_smaller_string_in(roman_numeral_string, "IIIII", "V");
  replace_string_with_smaller_string_in(roman_numeral_string, "IIII", "IV");
  replace_string_with_smaller_string_in(roman_numeral_string, "VV", "X");
  replace_string_with_smaller_string_in(roman_numeral_string, "XXXXX", "L");
  replace_string_with_smaller_string_in(roman_numeral_string, "XXXX", "XL");
  replace_string_with_smaller_string_in(roman_numeral_string, "LL", "C");
  replace_string_with_smaller_string_in(roman_numeral_string, "CCCCC", "D");
  replace_string_with_smaller_string_in(roman_numeral_string, "DD", "M");
}

/**
Expanding Roman Numerals
IV -> IIII +2
IX -> VIIII +3
XL -> XXXX +2
XC -> LXXXX +3
CD -> CCCC +2
CM -> DCCCC +3
The string grows by at most 15 characters when expanding.
**/

char *new_expanded_roman_numeral_string(char *roman_numeral_string) {
  size_t length_input_string = strlen(roman_numeral_string);
  size_t length_expanded_string = length_input_string;
  char *expanded_string =
      malloc((length_input_string + 15) * sizeof(*expanded_string));
  memcpy(expanded_string, roman_numeral_string, length_input_string);
  expanded_string[length_expanded_string] = '\0';
  char *first_entry = strstr(roman_numeral_string, "IV");
  if (first_entry != NULL) {
    ptrdiff_t index = first_entry - roman_numeral_string;
    memmove(&expanded_string[index + 4], &expanded_string[index + 2],
            strlen(&expanded_string[index + 2]));
    memcpy(&expanded_string[index], "IIII", 4);
    length_expanded_string += 2;
    expanded_string[length_expanded_string] = '\0';
  }
  first_entry = strstr(roman_numeral_string, "XL");
  if (first_entry != NULL) {
    ptrdiff_t index = first_entry - roman_numeral_string;
    memmove(&expanded_string[index + 4], &expanded_string[index + 2],
            strlen(&expanded_string[index + 2]));
    memcpy(&expanded_string[index], "XXXX", 4);
    length_expanded_string += 2;
    expanded_string[length_expanded_string] = '\0';
  }
  return expanded_string;
}

char *eat_characters_from_string(char *text_to_write_into,
                                 char *text_to_pull_from, char character,
                                 size_t *ptr_cursor_into) {
  size_t cursor_into = *ptr_cursor_into;
  size_t cursor_from = 0;
  while (text_to_pull_from[cursor_from] == character) {
    text_to_write_into[cursor_into] = character;
    cursor_into++;
    cursor_from++;
  }
  *ptr_cursor_into = cursor_into;
  return &text_to_pull_from[cursor_from];
}

char *interleave_roman_numerals(char *augend, char *addend) {
  char *temp1 = new_expanded_roman_numeral_string(augend);
  char *temp2 = new_expanded_roman_numeral_string(addend);
  char *ptr_augend = temp1;
  char *ptr_addend = temp2;
  size_t length_augend = strlen(temp1);
  size_t length_addend = strlen(temp2);
  size_t length_result = length_augend + length_addend;
  char *result = malloc((length_result + 1) * sizeof(*(result)));
  assert(result != NULL);

  size_t cursor_result = 0;
  char valid_numerals[8] = "MDCLXVI";
  for (size_t i = 0; i < strlen(valid_numerals); i++) {
    ptr_augend = eat_characters_from_string(result, ptr_augend,
                                            valid_numerals[i], &cursor_result);
    ptr_addend = eat_characters_from_string(result, ptr_addend,
                                            valid_numerals[i], &cursor_result);
  }

  result[length_result] = '\0';
  free(temp1);
  free(temp2);
  return result;
}

char *add_roman_numerals(char *augend, char *addend) {
  char *result = interleave_roman_numerals(augend, addend);
  normalize_roman_numeral_string(result);

  return result;
}
