#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include "roman.h"

void dangerous_string_replace(char *text, char *text_to_be_replaced,
                              char *text_to_replace_it) {
  /*************************************************************************************************
  Only call this function on text that you know has enough allocated space to
  have the characters
  be safely replaced.

  If the replacing text is shorter than the text to be replaced, it can be
  safely called.
  ***************************************************************************************************/
  char *entry = strstr(text, text_to_be_replaced);
  if (entry != NULL) {
    ptrdiff_t index = entry - text;
    size_t length_text = strlen(text);
    size_t length_text_to_be_replaced = strlen(text_to_be_replaced);
    size_t length_text_to_replace_it = strlen(text_to_replace_it);
    memmove(&text[index + length_text_to_replace_it],
            &text[index + length_text_to_be_replaced],
            length_text - length_text_to_be_replaced - index);
    memcpy(&text[index], text_to_replace_it, length_text_to_replace_it);
    length_text -= length_text_to_be_replaced - length_text_to_replace_it;
    text[length_text] = '\0';
  }
}

/**************************
Contracting Roman Numerals.
IIII -> IV
VIIII -> IX
XXXX -> XL
LXXXX -> XC
CCCC -> CD
DCCCC -> CM
***************************/

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
    /***************************************************************
    This call should always be safe.
    ****************************************************************/
    dangerous_string_replace(text, longer_string, shorter_string);
  }
}

void normalize_roman_numeral_string(char *roman_numeral_string) {
  replace_string_with_smaller_string_in(roman_numeral_string, "IIIII", "V");
  replace_string_with_smaller_string_in(roman_numeral_string, "VV", "X");
  replace_string_with_smaller_string_in(roman_numeral_string, "XXXXX", "L");
  replace_string_with_smaller_string_in(roman_numeral_string, "LL", "C");
  replace_string_with_smaller_string_in(roman_numeral_string, "CCCCC", "D");
  replace_string_with_smaller_string_in(roman_numeral_string, "DD", "M");

  replace_string_with_smaller_string_in(roman_numeral_string, "DCCCC", "CM");
  replace_string_with_smaller_string_in(roman_numeral_string, "CCCC", "CD");
  replace_string_with_smaller_string_in(roman_numeral_string, "LXXXX", "XC");
  replace_string_with_smaller_string_in(roman_numeral_string, "XXXX", "XL");
  replace_string_with_smaller_string_in(roman_numeral_string, "VIIII", "IX");
  replace_string_with_smaller_string_in(roman_numeral_string, "IIII", "IV");
}

/***********************************************************
Expanding Roman Numerals
IV -> IIII +2
IX -> VIIII +3
XL -> XXXX +2
XC -> LXXXX +3
CD -> CCCC +2
CM -> DCCCC +3
The string grows by at most 15 characters when expanding.
************************************************************/

char *new_expanded_roman_numeral_string(char *roman_numeral_string) {
  size_t length_input_string = strlen(roman_numeral_string);
  size_t length_expanded_string = length_input_string;
  char *expanded_string =
      malloc((length_input_string + 15) * sizeof(*expanded_string));
  assert(expanded_string != NULL);
  memcpy(expanded_string, roman_numeral_string, length_input_string);
  expanded_string[length_expanded_string] = '\0';

  /************************************************************
  The following calls are only safe in this context as we have
  allocated enough space for the expansions.
  *************************************************************/
  dangerous_string_replace(expanded_string, "IV", "IIII");
  dangerous_string_replace(expanded_string, "IX", "VIIII");
  dangerous_string_replace(expanded_string, "XL", "XXXX");
  dangerous_string_replace(expanded_string, "XC", "LXXXX");
  dangerous_string_replace(expanded_string, "CD", "CCCC");
  dangerous_string_replace(expanded_string, "CM", "DCCCC");

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
  size_t length_augend = strlen(augend);
  size_t length_addend = strlen(addend);
  size_t length_result = length_augend + length_addend;
  char *result = malloc((length_result + 1) * sizeof(*(result)));
  assert(result != NULL);

  size_t cursor_result = 0;
  char valid_numerals[8] = "MDCLXVI";
  for (size_t i = 0; i < strlen(valid_numerals); i++) {
    augend = eat_characters_from_string(result, augend, valid_numerals[i],
                                        &cursor_result);
    addend = eat_characters_from_string(result, addend, valid_numerals[i],
                                        &cursor_result);
  }

  result[length_result] = '\0';

  return result;
}

char *add_roman_numerals(char *augend, char *addend) {
  char *expanded_augend = new_expanded_roman_numeral_string(augend);
  char *expanded_addend = new_expanded_roman_numeral_string(addend);

  char *result = interleave_roman_numerals(expanded_augend, expanded_addend);

  normalize_roman_numeral_string(result);

  free(expanded_augend);
  free(expanded_addend);

  return result;
}
