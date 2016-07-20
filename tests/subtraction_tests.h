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
