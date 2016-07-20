#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include "string_functions.h"
#include "roman.h"

char numeral_order[] = "MDCLXVI";
char carry_order[] = "IVXLCDM";

int numeral_comparison_function(const void *roman_numeral_1,
                                const void *roman_numeral_2) {

  char numeral_1 = *((char *)roman_numeral_1);
  char numeral_2 = *((char *)roman_numeral_2);
  return (int)(strchr(numeral_order, numeral_1) -
               strchr(numeral_order, numeral_2));
}

void order_roman_numeral(char *roman_numeral) {

  qsort(roman_numeral, strlen(roman_numeral), sizeof(*roman_numeral),
        numeral_comparison_function);
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

char *add_roman_numerals(char *augend, char *addend) {
  char *expanded_augend = new_expanded_roman_numeral_string(augend);
  char *expanded_addend = new_expanded_roman_numeral_string(addend);

  char *result = new_concatenated_string(expanded_augend, expanded_addend);
  order_roman_numeral(result);
  normalize_roman_numeral_string(result);

  free(expanded_augend);
  free(expanded_addend);

  return result;
}

void carry_roman_numeral(char *roman_numeral, char subtrahend_numeral) {
  size_t carry_length = strlen(carry_order);
  char *entry = strchr(carry_order, subtrahend_numeral);
  size_t index = entry - carry_order;
  for (size_t i = index + 1; i < carry_length; i++) {
    char *carry_entry = strchr(roman_numeral, carry_order[i]);
    if (carry_entry != NULL) {
      if (carry_order[i] == 'V') {
        dangerous_string_replace(roman_numeral, "V", "IIIII");
      } else if (carry_order[i] == 'X') {
        dangerous_string_replace(roman_numeral, "X", "VV");
      } else if (carry_order[i] == 'L') {
        dangerous_string_replace(roman_numeral, "L", "XXXXX");
      } else if (carry_order[i] == 'C') {
        dangerous_string_replace(roman_numeral, "C", "LL");
      } else if (carry_order[i] == 'D') {
        dangerous_string_replace(roman_numeral, "D", "CCCCC");
      } else if (carry_order[i] == 'M') {
        dangerous_string_replace(roman_numeral, "M", "DD");
      }
      if (carry_order[i - 1] != subtrahend_numeral) {
        carry_roman_numeral(roman_numeral, subtrahend_numeral);
      }
      break;
    }
  }
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

  for (size_t i = length_subtrahend; i > 0; i--) {
    char *entry = strchr(result, subtrahend[i - 1]);
    if (entry == NULL) {
      carry_roman_numeral(result, subtrahend[i - 1]);
    }
    replace_string_with_smaller_string_in(
        result, (char[]) { subtrahend[i - 1], '\0' }, "");
  }
  order_roman_numeral(result);
  normalize_roman_numeral_string(result);

  free(expanded_minuend);
  free(expanded_subtrahend);

  return result;
}
