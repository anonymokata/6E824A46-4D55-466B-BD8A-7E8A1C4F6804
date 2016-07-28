#include <check.h>
#include <stdbool.h>
#include <stdlib.h>

Suite *input_validation_suite(void);

START_TEST(test_I_is_valid) {
  bool result;
  result = validate_roman_numeral("I");
  ck_assert(result == true);
}
END_TEST

START_TEST(test_II_is_valid) {
  bool result;
  result = validate_roman_numeral("II");
  ck_assert(result == true);
}
END_TEST

START_TEST(test_IIII_is_not_valid) {
  bool result;
  result = validate_roman_numeral("IIII");
  ck_assert(result == false);
}
END_TEST

START_TEST(test_IV_is_valid) {
  bool result;
  result = validate_roman_numeral("IV");
  ck_assert(result == true);
}
END_TEST

START_TEST(test_VIII_is_valid) {
  bool result;
  result = validate_roman_numeral("VIII");
  ck_assert(result == true);
}
END_TEST

START_TEST(test_IX_is_valid) {
  bool result;
  result = validate_roman_numeral("IX");
  ck_assert(result == true);
}
END_TEST

START_TEST(test_XXX_is_valid) {
  bool result;
  result = validate_roman_numeral("XXX");
  ck_assert(result == true);
}
END_TEST

START_TEST(test_L_is_valid) {
  bool result;
  result = validate_roman_numeral("L");
  ck_assert(result == true);
}
END_TEST

Suite *input_validation_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Input Validation");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_I_is_valid);
  tcase_add_test(tc_core, test_II_is_valid);
  tcase_add_test(tc_core, test_IIII_is_not_valid);
  tcase_add_test(tc_core, test_IV_is_valid);
  tcase_add_test(tc_core, test_VIII_is_valid);
  tcase_add_test(tc_core, test_IX_is_valid);
  tcase_add_test(tc_core, test_XXX_is_valid);
  tcase_add_test(tc_core, test_L_is_valid);
  suite_add_tcase(s, tc_core);

  return s;
}
