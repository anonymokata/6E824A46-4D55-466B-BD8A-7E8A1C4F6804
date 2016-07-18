#include <check.h>
#include <stdlib.h>
#include "../src/roman.h"

START_TEST(test_one_plus_one) {
  char *result;
  result = add_roman_numerals("I", "I");
  ck_assert_str_eq(result, "II");
  free(result);
}
END_TEST

START_TEST(test_two_plus_two) {
  char *result;
  result = add_roman_numerals("II", "II");
  ck_assert_str_eq(result, "IV");
  free(result);
}
END_TEST

START_TEST(test_three_plus_three) {
  char *result;
  result = add_roman_numerals("III", "III");
  ck_assert_str_eq(result, "VI");
  free(result);
}
END_TEST

START_TEST(test_four_plus_four) {
  char *result;
  result = add_roman_numerals("IV", "IV");
  ck_assert_str_eq(result, "VIII");
  free(result);
}
END_TEST

START_TEST(test_five_plus_five) {
  char *result;
  result = add_roman_numerals("V", "V");
  ck_assert_str_eq(result, "X");
  free(result);
}
END_TEST

Suite *addition_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Addition");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_one_plus_one);
  tcase_add_test(tc_core, test_two_plus_two);
  tcase_add_test(tc_core, test_three_plus_three);
  tcase_add_test(tc_core, test_four_plus_four);
  tcase_add_test(tc_core, test_five_plus_five);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {

  int number_failed;
  Suite *s;
  SRunner *sr;

  s = addition_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
