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
