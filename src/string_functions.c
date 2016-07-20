#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

char *new_concatenated_string(char *starting_string, char *ending_string) {
  /************************************************************************
  Concatenates two strings together and allocates space on the heap for them
  be sure to free the result!
  ************************************************************************/
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

void dangerous_string_replace(char *text, char *text_to_be_replaced,
                              char *text_to_replace_it) {
  /***************************************************************************
  Only call this function on text that you know has enough allocated space to
  have the characters be safely replaced.

  If the replacing text is shorter than the text to be replaced, it can be
  safely called.
  *****************************************************************************/
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

void replace_string_with_smaller_string_in(char *text, char *longer_string,
                                           char *shorter_string) {
  /************************************************************************
  Wrapper function for dangerous_string_replace, for the case when it is
  safe to call it. Replaces the longer_string in the text with the shorter
  string. Calling with the null string as the shorter string deletes the
  longer string from the text.
  ************************************************************************/
  size_t length_text = strlen(text);
  assert(length_text > 0);
  size_t length_longer_string = strlen(longer_string);
  assert(length_longer_string > 0);
  size_t length_shorter_string = strlen(shorter_string);
  assert(length_shorter_string < length_longer_string);
  if (length_text >= length_longer_string) {
    /***************************************************************
    This call should always be safe.
    ****************************************************************/
    dangerous_string_replace(text, longer_string, shorter_string);
  }
}
