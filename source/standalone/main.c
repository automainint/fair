#include "../fair/fair.h"

#include <string.h>

#ifdef FAIR_ENABLE_TESTING
int run_tests();
#endif

int main(int argc, char **argv) {
#ifdef FAIR_ENABLE_TESTING
  for (int i = 0; i < argc; i++)
    if (strcmp("--test", argv[i]) == 0)
      return run_tests();
#endif

  return fair_run(argc, argv);
}
