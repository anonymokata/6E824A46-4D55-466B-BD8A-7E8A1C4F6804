#include "roman.h"
#include "string_functions.h"
#include <assert.h>
#include <regex.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define COLS(A) sizeof(A[0]) / sizeof(A[0][0])

/*********************************
Numerals are typically written from
largest value to smallest.
**********************************/
static const char numeral_order[] = "MDCLXVI";
/********************************
When carrying during subtraction
we first try the smallest value
we can.
********************************/
static const char carry_order[] = "IVXLCDM";

/************************************
Roman Numeral Values.
V = IIIII
X = VV
L = XXXXX
C = LL
D = CCCCC
M = DD
*************************************/

static const char *numeral_values[2][6] = { { "V", "X", "L", "C", "D", "M" },
                                            { "IIIII", "VV", "XXXXX", "LL",
                                              "CCCCC", "DD" } };

/**************************
Contracting Roman Numerals.
IIII -> IV
VIIII -> IX
XXXX -> XL
LXXXX -> XC
CCCC -> CD
DCCCC -> CM
***************************/
static const char *numeral_subtractive_form[2][6] = {
  { "IV", "IX", "XL", "XC", "CD", "CM" },
  { "IIII", "VIIII", "XXXX", "LXXXX", "CCCC", "DCCCC" }
};

bool validate_roman_numeral(const char *input) {
  regex_t expression;
  int reg_exp_error_val =
      regcomp(&expression, "^(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$",
              REG_NOSUB | REG_EXTENDED);
  assert(reg_exp_error_val == 0);
  int reg_exp_match_val = regexec(&expression, input, 0, NULL, 0);
  regfree(&expression);
  if (reg_exp_match_val == 0) {
    return true;
  } else {
    return false;
  }
}

static int numeral_comparison_function(const void *restrict roman_numeral_1,
                                       const void *restrict roman_numeral_2) {
  /***********************************************************
  Helper function for use in qsort. Meant to be used on
  expanded roman numerals only.
  ***********************************************************/

  char numeral_1 = *((const char *)roman_numeral_1);
  char numeral_2 = *((const char *)roman_numeral_2);
  return (int)(strchr(numeral_order, numeral_1) -
               strchr(numeral_order, numeral_2));
}

static void order_roman_numeral(char *restrict roman_numeral) {
  /**********************************************
  Orders roman numerals from largest value to
  smallest value, assumes it is already expanded.
  If the roman numeral is in subtractive form,
  this function will ruin the value of the roman
  numeral.
  ***********************************************/
  qsort(roman_numeral, strlen(roman_numeral), sizeof(*roman_numeral),
        numeral_comparison_function);
}

static void
normalize_roman_numeral_string(char *restrict roman_numeral_string) {
  /**************************************************************
  Takes a roman numeral string in expanded form and puts it into
  subtractive form.
  ***************************************************************/
  for (size_t i = 0; i < COLS(numeral_values); i++) {
    replace_string_with_smaller_string_in(
        roman_numeral_string, numeral_values[1][i], numeral_values[0][i]);
  }
  size_t columns_subtractive_form = COLS(numeral_subtractive_form);
  for (size_t i = 0; i < columns_subtractive_form; i++) {
    replace_string_with_smaller_string_in(
        roman_numeral_string,
        numeral_subtractive_form[1][columns_subtractive_form - 1 - i],
        numeral_subtractive_form[0][columns_subtractive_form - 1 - i]);
  }
}

static char *
new_expanded_roman_numeral_string(const char *restrict roman_numeral_string) {
  /***********************************************************
  Takes a roman numeral in subtractive form and expands it,
  allocating space for the new string on the heap, so be sure
  to free it!

  Expanding Roman Numerals
  IV -> IIII +2
  IX -> VIIII +3
  XL -> XXXX +2
  XC -> LXXXX +3
  CD -> CCCC +2
  CM -> DCCCC +3
  The string grows by at most 15 characters when expanding.
  ************************************************************/

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
  for (size_t i = 0; i < COLS(numeral_subtractive_form); i++) {
    dangerous_string_replace(expanded_string, numeral_subtractive_form[0][i],
                             numeral_subtractive_form[1][i]);
  }

  return expanded_string;
}

char *add_roman_numerals(const char *augend, const char *addend) {
  /***************************************************
  Adds two strings containing roman numerals together
  and returns a newly allocated string. Be sure to
  free the result!
  ****************************************************/

  char *expanded_augend = new_expanded_roman_numeral_string(augend);
  char *expanded_addend = new_expanded_roman_numeral_string(addend);

  char *result = new_concatenated_string(expanded_augend, expanded_addend);
  order_roman_numeral(result);
  normalize_roman_numeral_string(result);

  free(expanded_augend);
  free(expanded_addend);

  return result;
}

static void carry_roman_numeral(char *restrict roman_numeral,
                                const char subtrahend_numeral) {
  /*********************************************************************
  This function expands the roman numeral given so that
  subtrahend_numeral can be subtracted from it. Be sure to allocate
  enough extra space for the expanded roman numeral before calling!
  *********************************************************************/
  size_t carry_length = strlen(carry_order);
  char *entry = strchr(carry_order, subtrahend_numeral);
  ptrdiff_t index_pd = entry - carry_order;
  assert(index_pd >= 0);
  size_t index = (size_t)index_pd;
  for (size_t i = index + 1; i < carry_length; i++) {
    char *carry_entry = strchr(roman_numeral, carry_order[i]);
    if (carry_entry != NULL) {
      for (size_t j = 0; j < 6; j++) {
        if (carry_order[i] == numeral_values[0][j][0]) {
          dangerous_string_replace(roman_numeral, numeral_values[0][j],
                                   numeral_values[1][j]);
          break;
        }
      }
      if (carry_order[i - 1] != subtrahend_numeral) {
        carry_roman_numeral(roman_numeral, subtrahend_numeral);
      }
      break;
    }
  }
}

char *subtract_roman_numerals(const char *minuend, const char *subtrahend) {
  /***************************************************************
  Subtracts two strings containing roman numerals from each other
  and returns a newly allocated string. Be sure to free the result!
  ****************************************************************/
  char *expanded_minuend = new_expanded_roman_numeral_string(minuend);
  char *expanded_subtrahend = new_expanded_roman_numeral_string(subtrahend);
  size_t length_minuend = strlen(expanded_minuend);
  size_t length_subtrahend = strlen(expanded_subtrahend);
  /************************************************************************
  The longest expansion ought to be from M-I = CMXCIX=DCCCCLXXXXVIIII fully
  expanded, will recalculate the maximum expansion more throughly later.
  *************************************************************************/
  char *result = malloc((16 + length_minuend) * (sizeof(*result)));
  memcpy(result, expanded_minuend, length_minuend);
  result[length_minuend] = '\0';

  for (size_t i = length_subtrahend; i > 0; i--) {
    char *entry = strchr(result, expanded_subtrahend[i - 1]);
    if (entry == NULL) {
      carry_roman_numeral(result, expanded_subtrahend[i - 1]);
    }
    delete_character_from_string_once(result, expanded_subtrahend[i - 1]);
  }

  order_roman_numeral(result);
  normalize_roman_numeral_string(result);

  free(expanded_minuend);
  free(expanded_subtrahend);

  return result;
}
