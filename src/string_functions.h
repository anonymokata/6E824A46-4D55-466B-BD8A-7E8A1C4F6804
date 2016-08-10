#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#include <stddef.h>

char *new_concatenated_string(const char *restrict starting_string,
                              const char *restrict ending_string);

char *new_padded_string_from_string(const char *restrict original_string,
                                    size_t additional_padding);

// Be careful when calling the function below. Make sure enough space
// is allocated.
void dangerous_string_replace(char *restrict text,
                              const char *restrict text_to_be_replaced,
                              const char *restrict text_to_replace_it);

void replace_string_with_smaller_string_in(char *restrict text,
                                           const char *restrict longer_string,
                                           const char *restrict shorter_string);

void delete_character_from_string_once(char *restrict text,
                                       const char character);

#endif /* STRING_FUNCTIONS_H */
