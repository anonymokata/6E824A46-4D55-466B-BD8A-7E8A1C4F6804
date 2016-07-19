START_TEST(test_two_minus_one) {
  char *result;
  result = subtract_roman_numerals("II", "I");
  ck_assert_str_eq(result, "I");
  free(result);
}
END_TEST
