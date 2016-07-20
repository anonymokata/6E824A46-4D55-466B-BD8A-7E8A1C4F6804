#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

char *new_concatenated_string(char *starting_string, char *ending_string);

void dangerous_string_replace(char *text, char *text_to_be_replaced,
                              char *text_to_replace_it);

char *eat_characters_from_string(char *text_to_write_into,
                                 char *text_to_pull_from, char character,
                                 size_t *ptr_cursor_into);

void replace_string_with_smaller_string_in(char *text, char *longer_string,
                                           char *shorter_string);

#endif /* STRING_FUNCTIONS_H */
