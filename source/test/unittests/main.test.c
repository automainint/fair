#include "test.h"

#include <stdio.h>
#include <time.h>

struct fair_tests_list fair_tests_list = { 0 };

static void report(ptrdiff_t i, bool ok) {
  if (!ok)
    fair_tests_list.tests[i].test_status = false;
}

static long long ns_to_ms(long long ns) {
  return (ns + 500000) / 1000000;
}

static long long sec_to_ms(long long sec) {
  return 1000 * sec;
}

int run_tests() {
  int status = 0;

  for (ptrdiff_t i = 0; i < fair_tests_list.size; i++) {
    printf("[ RUN    ] %s\n", fair_tests_list.tests[i].test_name);

    struct timespec begin, end;
    timespec_get(&begin, TIME_UTC);

    fair_tests_list.tests[i].test_fn(i, report);

    timespec_get(&end, TIME_UTC);
    int duration = (int) (ns_to_ms(end.tv_nsec - begin.tv_nsec) +
                          sec_to_ms(end.tv_sec - begin.tv_sec));

    if (fair_tests_list.tests[i].test_status == false) {
      printf("[ FAILED ] %s - %d ms\n",
             fair_tests_list.tests[i].test_name, duration);
      status = 1;
    } else {
      printf("[     OK ] %s - %d ms\n",
             fair_tests_list.tests[i].test_name, duration);
    }
  }

  return status;
}
