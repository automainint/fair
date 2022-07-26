#include "test.h"

#include <stdio.h>

struct fair_tests_list fair_tests_list = { 0 };

static void report(ptrdiff_t i, bool ok) {
  if (!ok)
    fair_tests_list.tests[i].test_status = false;
}

int run_tests() {
  int status = 0;

  for (ptrdiff_t i = 0; i < fair_tests_list.size; i++) {
    fair_tests_list.tests[i].test_fn(i, report);

    if (fair_tests_list.tests[i].test_status == false) {
      printf("[ FAILED ] %s\n", fair_tests_list.tests[i].test_name);
      status = 1;
    } else {
      printf("[ OK     ] %s\n", fair_tests_list.tests[i].test_name);
    }
  }

  return status;
}
