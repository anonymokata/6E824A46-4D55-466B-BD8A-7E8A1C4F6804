#include <stdlib.h>
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

char *add_roman_numerals(char *augend, char *addend) {
  char *result = concatinate_strings(augend, addend);
  if (strcmp(result, "IIII") == 0) {
    strcpy(result, "IV");
  }

  return result;
}
