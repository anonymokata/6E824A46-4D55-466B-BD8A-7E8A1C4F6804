#include <check.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../src/roman.h"
#include "addition_tests.h"
#include "additive_inverse_tests.h"
#include "input_validation_tests.h"
#include "subtraction_tests.h"

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
  tcase_add_test(tc_core, test_fourteen_plus_sixty);
  tcase_add_test(tc_core, test_fourhundred_plus_fortyfour);
  tcase_add_test(tc_core, test_ninehundred_plus_fortyfour);
  tcase_add_test(tc_core, test_nine_plus_ninety);
  suite_add_tcase(s, tc_core);

  return s;
}

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

Suite *additive_inverse_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Additive_Inverse");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_additive_inverse);
  suite_add_tcase(s, tc_core);

  return s;
}

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

  s = subtraction_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  s = additive_inverse_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  s = input_validation_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
