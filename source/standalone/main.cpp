#include "../fair/fair.h"

#ifdef FAIR_ENABLE_TESTING
#  define CATCH_CONFIG_RUNNER
#  include <catch2/catch.hpp>

auto run_tests(int argc, char **argv) -> int {
  return Catch::Session().run(argc, argv);
}
#endif

auto main(int argc, char **argv) -> int {
#ifdef FAIR_ENABLE_TESTING
  using namespace std::literals;

  for (int i = 0; i < argc; i++)
    if ("--test"sv == argv[i]) {
      static char empty[] = "";
      argv[i]             = empty;
      return run_tests(argc, argv);
    }
#endif

  return fair::run(argc, argv);
}
