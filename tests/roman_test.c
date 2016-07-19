#include <check.h>
#include <stdlib.h>
#include "../src/roman.h"
#include "addition_tests.h"

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
