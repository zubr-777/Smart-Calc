#ifndef SRC_TEST_H_
#define SRC_TEST_H_

#include <check.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#include "./backend/s21_smart_calc.h"

Suite *suite_string_parsing(void);

#endif // SRC_TEST_H_