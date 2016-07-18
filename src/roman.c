#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include "roman.h"

char *concatinate_strings(char *starting_string, char *ending_string) {
  char *result;
  size_t length_starting_string = strlen(starting_string);
  assert(length_starting_string > 0);
  size_t length_ending_string = strlen(ending_string);
  assert(length_ending_string > 0);
  size_t length_result = length_starting_string + length_ending_string;
  assert(length_result > 0);
  result = malloc((length_result + 1) * sizeof(*(result)));
  assert(result != NULL);
  result[0] = '\0'; // ensure string starts with a null byte for strcat.
  strcat(result, starting_string);
  strcat(result, ending_string);
  return result;
}

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
  replace_string_with_smaller_string_in(roman_numeral_string, "LL", "C");
  replace_string_with_smaller_string_in(roman_numeral_string, "CCCCC", "D");
}

char *new_expanded_roman_numeral_string(char *roman_numeral_string) {
  size_t length_input_string = strlen(roman_numeral_string);
  char *expanded_string;
  char *first_entry = strstr(roman_numeral_string, "IV");
  if (first_entry != NULL) {
    expanded_string =
        malloc((length_input_string + 2) * sizeof(*expanded_string));
    ptrdiff_t index = first_entry - roman_numeral_string;
    memcpy(expanded_string, roman_numeral_string, index);
    memcpy(&expanded_string[index], "IIII", 4);
    memcpy(&expanded_string[index + 4], &first_entry[2],
           length_input_string - index);
    expanded_string[length_input_string + 2] = '\0';
  } else {
    expanded_string = malloc((length_input_string) * sizeof(*expanded_string));
    memcpy(expanded_string, roman_numeral_string, length_input_string);
    expanded_string[length_input_string] = '\0';
  }
  return expanded_string;
}

char *add_roman_numerals(char *augend, char *addend) {

  char *temp1 = new_expanded_roman_numeral_string(augend);
  char *temp2 = new_expanded_roman_numeral_string(addend);

  char *result = concatinate_strings(temp1, temp2);

  normalize_roman_numeral_string(result);

  free(temp1);
  free(temp2);
  return result;
}
