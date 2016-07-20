#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include "string_functions.h"
#include "roman.h"

/**************************
Contracting Roman Numerals.
IIII -> IV
VIIII -> IX
XXXX -> XL
LXXXX -> XC
CCCC -> CD
DCCCC -> CM
***************************/

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

char *subtract_roman_numerals(char *minuend, char *subtrahend) {
  char *expanded_minuend = new_expanded_roman_numeral_string(minuend);
  char *expanded_subtrahend = new_expanded_roman_numeral_string(subtrahend);
  size_t length_minuend = strlen(expanded_minuend);
  size_t length_subtrahend = strlen(expanded_subtrahend);
  /*
  The longest expansion ought to be from M-I = CMXCIX=DCCCCLXXXXVIIII fully
  expanded, will recalculate the
  maximum expansion more throughly later.
  */
  char *result =
      malloc((20 + length_minuend + length_subtrahend) * (sizeof(*result)));
  memcpy(result, expanded_minuend, length_minuend);
  result[length_minuend] = '\0';
  for (size_t i = 0; i < length_subtrahend; i++) {
    char *entry = strchr(result, subtrahend[i]);
    if (entry == NULL) {
      dangerous_string_replace(result, "V", "IIIII");
      entry = strchr(result, subtrahend[i]);
      assert(entry != NULL);
    }
    replace_string_with_smaller_string_in(result,
                                          (char[]) { subtrahend[i], '\0' }, "");
  }

  normalize_roman_numeral_string(result);

  free(expanded_minuend);
  free(expanded_subtrahend);

  return result;
}
