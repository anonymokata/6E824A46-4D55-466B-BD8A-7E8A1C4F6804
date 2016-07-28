#include <check.h>
#include <stdlib.h>

Suite *additive_inverse_suite(void);

START_TEST(test_additive_inverse) {
  char *result;
  char *variable_1;
  char *variable_2;
  char *temp;
  variable_1 = malloc(2);
  variable_1[0] = 'I';
  variable_1[1] = '\0';
  variable_2 = NULL;
  for (size_t i = 0; i < 1000; i++) {
    free(variable_2);
    variable_2 = malloc(2);
    variable_2[0] = 'I';
    variable_2[1] = '\0';
    for (size_t j = 0; j < i; j++) {
      temp = add_roman_numerals(variable_1, variable_2);
      result = subtract_roman_numerals(temp, variable_2);
      ck_assert_str_eq(result, variable_1);
      free(result);
      free(temp);
      temp = add_roman_numerals(variable_2, "I");
      free(variable_2);
      variable_2 = temp;
    }
    temp = add_roman_numerals(variable_1, "I");
    free(variable_1);
    variable_1 = temp;
  }
  free(variable_1);
  free(variable_2);
}
END_TEST

Suite *additive_inverse_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Additive_Inverse");
  tc_core = tcase_create("Core");
  tcase_set_timeout(tc_core, 0);
  tcase_add_test(tc_core, test_additive_inverse);
  suite_add_tcase(s, tc_core);

  return s;
}
