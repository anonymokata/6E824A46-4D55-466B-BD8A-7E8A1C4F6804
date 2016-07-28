#include <check.h>
#include <stdlib.h>

Suite *subtraction_suite(void);

START_TEST(test_two_minus_one) {
  char *result;
  result = subtract_roman_numerals("II", "I");
  ck_assert_str_eq(result, "I");
  free(result);
}
END_TEST

START_TEST(test_five_minus_one) {
  char *result;
  result = subtract_roman_numerals("V", "I");
  ck_assert_str_eq(result, "IV");
  free(result);
}
END_TEST

START_TEST(test_ten_minus_one) {
  char *result;
  result = subtract_roman_numerals("X", "I");
  ck_assert_str_eq(result, "IX");
  free(result);
}
END_TEST

START_TEST(test_fifty_minus_one) {
  char *result;
  result = subtract_roman_numerals("L", "I");
  ck_assert_str_eq(result, "XLIX");
  free(result);
}
END_TEST

START_TEST(test_onehundred_minus_one) {
  char *result;
  result = subtract_roman_numerals("C", "I");
  ck_assert_str_eq(result, "XCIX");
  free(result);
}
END_TEST

START_TEST(test_fivehundred_minus_one) {
  char *result;
  result = subtract_roman_numerals("D", "I");
  ck_assert_str_eq(result, "CDXCIX");
  free(result);
}
END_TEST

START_TEST(test_onethousand_minus_one) {
  char *result;
  result = subtract_roman_numerals("M", "I");
  ck_assert_str_eq(result, "CMXCIX");
  free(result);
}
END_TEST

START_TEST(test_three_minus_two) {
  char *result;
  result = subtract_roman_numerals("III", "II");
  ck_assert_str_eq(result, "I");
  free(result);
}
END_TEST

START_TEST(test_six_minus_five) {
  char *result;
  result = subtract_roman_numerals("VI", "V");
  ck_assert_str_eq(result, "I");
  free(result);
}
END_TEST

START_TEST(test_five_minus_four) {
  char *result;
  result = subtract_roman_numerals("V", "IV");
  ck_assert_str_eq(result, "I");
  free(result);
}
END_TEST

Suite *subtraction_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Subtraction");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_two_minus_one);
  tcase_add_test(tc_core, test_five_minus_one);
  tcase_add_test(tc_core, test_ten_minus_one);
  tcase_add_test(tc_core, test_fifty_minus_one);
  tcase_add_test(tc_core, test_onehundred_minus_one);
  tcase_add_test(tc_core, test_fivehundred_minus_one);
  tcase_add_test(tc_core, test_onethousand_minus_one);
  tcase_add_test(tc_core, test_three_minus_two);
  tcase_add_test(tc_core, test_six_minus_five);
  tcase_add_test(tc_core, test_five_minus_four);
  suite_add_tcase(s, tc_core);

  return s;
}
