#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

void dangerous_string_replace(char *text, char *text_to_be_replaced,
                              char *text_to_replace_it) {
  /*************************************************************************************************
  Only call this function on text that you know has enough allocated space to
  have the characters
  be safely replaced.

  If the replacing text is shorter than the text to be replaced, it can be
  safely called.
  ***************************************************************************************************/
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

char *eat_characters_from_string(char *text_to_write_into,
                                 char *text_to_pull_from, char character,
                                 size_t *ptr_cursor_into) {
  size_t cursor_into = *ptr_cursor_into;
  size_t cursor_from = 0;
  while (text_to_pull_from[cursor_from] == character) {
    text_to_write_into[cursor_into] = character;
    cursor_into++;
    cursor_from++;
  }
  *ptr_cursor_into = cursor_into;
  return &text_to_pull_from[cursor_from];
}

void replace_string_with_smaller_string_in(char *text, char *longer_string,
                                           char *shorter_string) {
  size_t length_text = strlen(text);
  assert(length_text > 0);
  size_t length_longer_string = strlen(longer_string);
  assert(length_longer_string > 0);
  size_t length_shorter_string = strlen(shorter_string);
  // assert(length_shorter_string >= 0);
  assert(length_shorter_string < length_longer_string);
  if (length_text >= length_longer_string) {
    /***************************************************************
    This call should always be safe.
    ****************************************************************/
    dangerous_string_replace(text, longer_string, shorter_string);
  }
}
