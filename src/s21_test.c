#include "s21_test.h"

int main(void) {
  int failed = 0;

  Suite *s21_calc_test[] = {
    suite_string_parsing(),
    NULL};

  for (int i = 0; s21_calc_test[i] != NULL; i++) {  // (&& failed == 0)
    SRunner *sr = srunner_create(s21_calc_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}