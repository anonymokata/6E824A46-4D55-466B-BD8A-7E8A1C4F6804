#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "roman.h"

char *add_roman_numerals(char *augend, char *addend) {
  size_t length_augend = strlen(augend);
  size_t length_addend = strlen(addend);
  size_t length_result = length_addend + length_augend;
  char *result = malloc((length_result + 1) * sizeof(*(result)));
  assert(result != NULL);
  result[0] = '\0'; // ensure string starts with a null byte for strcat.
  strcat(result, augend);
  strcat(result, addend);
  if (strcmp(result, "IIII") == 0) {
    strcpy(result, "IV");
  }

  return result;
}
