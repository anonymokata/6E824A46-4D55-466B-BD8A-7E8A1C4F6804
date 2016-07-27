Suite *addition_suite(void);

START_TEST(test_one_plus_one) {
  char *result;
  result = add_roman_numerals("I", "I");
  ck_assert_str_eq(result, "II");
  free(result);
}
END_TEST

START_TEST(test_two_plus_two) {
  char *result;
  result = add_roman_numerals("II", "II");
  ck_assert_str_eq(result, "IV");
  free(result);
}
END_TEST

START_TEST(test_three_plus_three) {
  char *result;
  result = add_roman_numerals("III", "III");
  ck_assert_str_eq(result, "VI");
  free(result);
}
END_TEST

START_TEST(test_four_plus_four) {
  char *result;
  result = add_roman_numerals("IV", "IV");
  ck_assert_str_eq(result, "VIII");
  free(result);
}
END_TEST

START_TEST(test_five_plus_five) {
  char *result;
  result = add_roman_numerals("V", "V");
  ck_assert_str_eq(result, "X");
  free(result);
}
END_TEST

START_TEST(test_thirty_plus_twenty) {
  char *result;
  result = add_roman_numerals("XXX", "XX");
  ck_assert_str_eq(result, "L");
  free(result);
}
END_TEST

START_TEST(test_fifty_plus_fifty) {
  char *result;
  result = add_roman_numerals("L", "L");
  ck_assert_str_eq(result, "C");
  free(result);
}
END_TEST

START_TEST(test_twohundred_plus_threehundred) {
  char *result;
  result = add_roman_numerals("CC", "CCC");
  ck_assert_str_eq(result, "D");
  free(result);
}
END_TEST

START_TEST(test_fivehundred_plus_fivehundred) {
  char *result;
  result = add_roman_numerals("D", "D");
  ck_assert_str_eq(result, "M");
  free(result);
}
END_TEST

START_TEST(test_six_plus_six) {
  char *result;
  result = add_roman_numerals("VI", "VI");
  ck_assert_str_eq(result, "XII");
  free(result);
}
END_TEST

START_TEST(test_forty_plus_eight) {
  char *result;
  result = add_roman_numerals("XL", "VIII");
  ck_assert_str_eq(result, "XLVIII");
  free(result);
}
END_TEST

START_TEST(test_nine_plus_nine) {
  char *result;
  result = add_roman_numerals("IX", "IX");
  ck_assert_str_eq(result, "XVIII");
  free(result);
}
END_TEST

START_TEST(test_ninety_plus_ninety) {
  char *result;
  result = add_roman_numerals("XC", "XC");
  ck_assert_str_eq(result, "CLXXX");
  free(result);
}
END_TEST

START_TEST(test_fourhundred_plus_fourhundred) {
  char *result;
  result = add_roman_numerals("CD", "CD");
  ck_assert_str_eq(result, "DCCC");
  free(result);
}
END_TEST

START_TEST(test_ninehundred_plus_ninehundred) {
  char *result;
  result = add_roman_numerals("CM", "CM");
  ck_assert_str_eq(result, "MDCCC");
  free(result);
}
END_TEST

START_TEST(test_fourteen_plus_sixty) {
  char *result;
  result = add_roman_numerals("XIV", "LX");
  ck_assert_str_eq(result, "LXXIV");
  free(result);
}
END_TEST

START_TEST(test_fourhundred_plus_fortyfour) {
  char *result;
  result = add_roman_numerals("CD", "XLIV");
  ck_assert_str_eq(result, "CDXLIV");
  free(result);
}
END_TEST

START_TEST(test_ninehundred_plus_fortyfour) {
  char *result;
  result = add_roman_numerals("CM", "XLIV");
  ck_assert_str_eq(result, "CMXLIV");
  free(result);
}
END_TEST

START_TEST(test_nine_plus_ninety) {
  char *result;
  result = add_roman_numerals("IX", "XC");
  ck_assert_str_eq(result, "XCIX");
  free(result);
}
END_TEST
