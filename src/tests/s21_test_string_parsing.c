#include "../s21_test.h"

START_TEST(string_parsing_0) {
  char *src = "sin(-0.69) - 9.3^x + xmod(+x+1)*acos(-1)";
  double x = 1;
  double result;
  double result_origin = sin(-0.69) - pow(9.3, x) + fmod(x,(+x+1))*acos(-1);
  calc_function(src, x, &result);
  ck_assert_double_eq(result_origin, result);
}
END_TEST

START_TEST(string_parsing_1) {
  char *src = "acos(cos(x))";
  double x = 1;
  double result;
  double result_origin = acos(cos(x));
  calc_function(src, x, &result);
  ck_assert_double_eq(result_origin, result);
}
END_TEST

START_TEST(string_parsing_2) {
  char *src = "asin(tan(x))";
  double x = 0;
  double result;
  double result_origin = asin(tan(x));
  calc_function(src, x, &result);
  ck_assert_double_eq(result_origin, result);
}
END_TEST

START_TEST(string_parsing_3) {
  char *src = "asin(atan(x))";
  double x = 0;
  double result;
  double result_origin = asin(atan(x));
  calc_function(src, x, &result);
  ck_assert_double_eq(result_origin, result);
}
END_TEST

START_TEST(string_parsing_4) {
  char *src = "sqrt(x)-ln(x)/log(x)";
  double x = 9;
  double result;
  double result_origin = sqrt(x)-log(x)/log10(x);
  calc_function(src, x, &result);
  ck_assert_double_eq(result_origin, result);
}
END_TEST

START_TEST(string_parsing_5) {
  char *src = "slog(x)";
  double x = 9;
  double result;
  int status = calc_function(src, x, &result);
  ck_assert_int_eq(1, status);
}
END_TEST

START_TEST(string_parsing_6) {
  char *src = "log(x";
  double x = 9;
  double result;
  int status = calc_function(src, x, &result);
  ck_assert_int_eq(2, status);
}
END_TEST

START_TEST(string_parsing_7) {
  char *src = "*";
  double x = 9;
  double result;
  int status = calc_function(src, x, &result);
  ck_assert_int_eq(1, status);
}
END_TEST

START_TEST(string_parsing_8) {
  char *src = "1/0";
  double x = 9;
  double result;
  int status = calc_function(src, x, &result);
  ck_assert_int_eq(2, status);
}
END_TEST

START_TEST(string_parsing_9) {
  char *src = "(-1)*(+2)";
  double x = 9;
  double result;
  int status = calc_function(src, x, &result);
  ck_assert_int_eq(0, status);
}
END_TEST

START_TEST(string_parsing_10) {
  char *src = "sqrt(-1)";
  double x = 9;
  double result;
  int status = calc_function(src, x, &result);
  ck_assert_int_eq(2, status);
}
END_TEST

START_TEST(string_parsing_11) {
  char *src = "1mod0";
  double x = 9;
  double result;
  int status = calc_function(src, x, &result);
  ck_assert_int_eq(2, status);
}
END_TEST

START_TEST(string_parsing_12) {
  char *src = "acos(2)";
  double x = 9;
  double result;
  int status = calc_function(src, x, &result);
  ck_assert_int_eq(2, status);
}
END_TEST

START_TEST(string_parsing_13) {
  char *src = "asin(2)";
  double x = 9;
  double result;
  int status = calc_function(src, x, &result);
  ck_assert_int_eq(2, status);
}
END_TEST

START_TEST(string_parsing_14) {
  char *src = "sqrt(-2)";
  double x = 9;
  double result;
  int status = calc_function(src, x, &result);
  ck_assert_int_eq(2, status);
}
END_TEST

START_TEST(string_parsing_15) {
  char *src = "ln(-2)";
  double x = 9;
  double result;
  int status = calc_function(src, x, &result);
  ck_assert_int_eq(2, status);
}
END_TEST

START_TEST(string_parsing_16) {
  char *src = "log(-2)";
  double x = 9;
  double result;
  int status = calc_function(src, x, &result);
  ck_assert_int_eq(2, status);
}
END_TEST

START_TEST(string_parsing_17) {
  char *src = "(-1)^0.4";
  double x = 9;
  double result;
  int status = calc_function(src, x, &result);
  ck_assert_int_eq(2, status);
}
END_TEST

START_TEST(string_parsing_18) {
  char *src = "0..4";
  double x = 9;
  double result;
  int status = calc_function(src, x, &result);
  ck_assert_int_eq(1, status);
}
END_TEST

START_TEST(string_parsing_19) {
  char *src = "(1.0)^0.4";
  double x = 9;
  double result;
  int status = calc_function(src, x, &result);
  ck_assert_int_eq(0, status);
}
END_TEST

START_TEST(string_parsing_20) {
  char *src = ")1(";
  double x = 9;
  double result;
  int status = calc_function(src, x, &result);
  ck_assert_int_eq(1, status);
}
END_TEST

Suite *suite_string_parsing(void) {
  Suite *s = suite_create("suite_string_parsing");
  TCase *tc = tcase_create("case_string_parsing");

  tcase_add_test(tc, string_parsing_0);
  tcase_add_test(tc, string_parsing_1);
  tcase_add_test(tc, string_parsing_2);
  tcase_add_test(tc, string_parsing_3);
  tcase_add_test(tc, string_parsing_4);
  tcase_add_test(tc, string_parsing_5);
  tcase_add_test(tc, string_parsing_6);
  tcase_add_test(tc, string_parsing_7);
  tcase_add_test(tc, string_parsing_8);
  tcase_add_test(tc, string_parsing_9);
  tcase_add_test(tc, string_parsing_10);
  tcase_add_test(tc, string_parsing_11);
  tcase_add_test(tc, string_parsing_12);
  tcase_add_test(tc, string_parsing_13);
  tcase_add_test(tc, string_parsing_14);
  tcase_add_test(tc, string_parsing_15);
  tcase_add_test(tc, string_parsing_16);
  tcase_add_test(tc, string_parsing_17);
  tcase_add_test(tc, string_parsing_18);
  tcase_add_test(tc, string_parsing_19);
  tcase_add_test(tc, string_parsing_20);

  suite_add_tcase(s, tc);
  return s;
}
