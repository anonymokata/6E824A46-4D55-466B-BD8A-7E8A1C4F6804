START_TEST(test_I_is_valid) {
  _Bool result;
  result = validate_roman_numeral("I");
  ck_assert(result == 0);
}
END_TEST
