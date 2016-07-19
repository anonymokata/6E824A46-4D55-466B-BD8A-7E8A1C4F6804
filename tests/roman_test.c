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

START_TEST(test_thirty_plus_twenty) {
  char *result;
  result = add_roman_numerals("XXX", "XX");
  ck_assert_str_eq(result, "L");
  free(result);
}
END_TEST

START_TEST(test_fifty_plus_fifty) {
  char *result;
  result = add_roman_numerals("L", "L");
  ck_assert_str_eq(result, "C");
  free(result);
}
END_TEST

START_TEST(test_twohundred_plus_threehundred) {
  char *result;
  result = add_roman_numerals("CC", "CCC");
  ck_assert_str_eq(result, "D");
  free(result);
}
END_TEST

START_TEST(test_fivehundred_plus_fivehundred) {
  char *result;
  result = add_roman_numerals("D", "D");
  ck_assert_str_eq(result, "M");
  free(result);
}
END_TEST

START_TEST(test_six_plus_six) {
  char *result;
  result = add_roman_numerals("VI", "VI");
  ck_assert_str_eq(result, "XII");
  free(result);
}
END_TEST

START_TEST(test_forty_plus_eight) {
  char *result;
  result = add_roman_numerals("XL", "VIII");
  ck_assert_str_eq(result, "XLVIII");
  free(result);
}
END_TEST

START_TEST(test_nine_plus_nine) {
  char *result;
  result = add_roman_numerals("IX", "IX");
  ck_assert_str_eq(result, "XVIII");
  free(result);
}
END_TEST

START_TEST(test_ninety_plus_ninety) {
  char *result;
  result = add_roman_numerals("XC", "XC");
  ck_assert_str_eq(result, "CLXXX");
  free(result);
}
END_TEST

START_TEST(test_fourhundred_plus_fourhundred) {
  char *result;
  result = add_roman_numerals("CD", "CD");
  ck_assert_str_eq(result, "DCCC");
  free(result);
}
END_TEST

START_TEST(test_ninehundred_plus_ninehundred) {
  char *result;
  result = add_roman_numerals("CM", "CM");
  ck_assert_str_eq(result, "MDCCC");
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
  tcase_add_test(tc_core, test_thirty_plus_twenty);
  tcase_add_test(tc_core, test_fifty_plus_fifty);
  tcase_add_test(tc_core, test_twohundred_plus_threehundred);
  tcase_add_test(tc_core, test_fivehundred_plus_fivehundred);
  tcase_add_test(tc_core, test_six_plus_six);
  tcase_add_test(tc_core, test_forty_plus_eight);
  tcase_add_test(tc_core, test_nine_plus_nine);
  tcase_add_test(tc_core, test_ninety_plus_ninety);
  tcase_add_test(tc_core, test_fourhundred_plus_fourhundred);
  tcase_add_test(tc_core, test_ninehundred_plus_ninehundred);
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
