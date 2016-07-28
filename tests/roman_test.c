#include "../src/roman.h"
#include "addition_tests.h"
#include "additive_inverse_tests.h"
#include "input_validation_tests.h"
#include "subtraction_tests.h"
#include <check.h>
#include <stdbool.h>

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
