#include "../fair/fair.h"

#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

auto run_tests(int argc, char **argv) -> int {
  return Catch::Session().run(argc, argv);
}

auto main(int argc, char **argv) -> int {
  using namespace std::literals;

  for (int i = 0; i < argc; i++)
    if ("--test"sv == argv[i]) {
      static char empty[] = "";
      argv[i]             = empty;
      return run_tests(argc, argv);
    }

  return fair::run(argc, argv);
}
