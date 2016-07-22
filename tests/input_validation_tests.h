START_TEST(test_I_is_valid) {
  _Bool result;
  result = validate_roman_numeral("I");
  ck_assert(result == true);
}
END_TEST

START_TEST(test_II_is_valid) {
  _Bool result;
  result = validate_roman_numeral("II");
  ck_assert(result == true);
}
END_TEST
