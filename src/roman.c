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

char *add_roman_numerals(char *augend, char *addend) {

  char *temp1 = malloc((strlen(augend) + 2) * sizeof(*temp1));
  char *temp2 = malloc((strlen(addend) + 2) * sizeof(*temp1));
  char *first_entry = strstr(augend, "IV");
  if (first_entry != NULL) {
    ptrdiff_t index = first_entry - augend;
    memcpy(temp1, augend, index);
    memcpy(&temp1[index], "IIII", 4);
    memcpy(&temp1[index + 4], &first_entry[2], strlen(augend) - index);
  } else {
    memcpy(temp1, augend, strlen(augend));
    temp1[strlen(augend)] = '\0';
  }
  first_entry = strstr(addend, "IV");
  if (first_entry != NULL) {
    ptrdiff_t index = first_entry - addend;
    memcpy(temp2, addend, index);
    memcpy(&temp2[index], "IIII", 4);
    memcpy(&temp2[index + 4], &first_entry[2], strlen(addend) - index);
  } else {
    memcpy(temp2, addend, strlen(addend));
    temp2[strlen(addend)] = '\0';
  }
  char *result = concatinate_strings(temp1, temp2);
  replace_string_with_smaller_string_in(result, "IIIII", "V");
  replace_string_with_smaller_string_in(result, "IIII", "IV");

  return result;
}
