#include "../../fair/array_ref.h"

#define FAIR_TEST_FILE array_ref
#include "test.h"

TEST("array ref equal") {
  int foo[] = { 1, 2, 3, 4, 5, 6, 7 };
  int bar[] = { 3, 4, 5 };

  FAIR_AR(foo_ref, int) = { .size = 3, .values = foo + 2 };
  FAIR_AR(bar_ref, int) = { .size = 3, .values = bar };

  REQUIRE(FAIR_AR_EQUAL(foo_ref, bar_ref));
}

static int compare(int const *left, int const *right) {
  return *left - *right;
}

TEST("array ref compare") {
  int foo[] = { 1, 2, 3, 5 };
  int bar[] = { 1, 2, 4, 5 };

  FAIR_AR(foo_ref, int) = { .size = 3, .values = foo };
  FAIR_AR(bar_ref, int) = { .size = 3, .values = bar };

  REQUIRE(FAIR_AR_COMPARE(foo_ref, bar_ref, compare) < 0);
  REQUIRE(FAIR_AR_COMPARE(bar_ref, foo_ref, compare) > 0);
  REQUIRE(FAIR_AR_COMPARE(foo_ref, foo_ref, compare) == 0);
}

TEST("array ref different element sizes") {
  int  foo[] = { 1, 2, 3 };
  char bar[] = { 1, 2, 3 };

  FAIR_AR(foo_ref, int)  = { .size = 3, .values = foo };
  FAIR_AR(bar_ref, char) = { .size = 3, .values = bar };

  REQUIRE(!FAIR_AR_EQUAL(foo_ref, bar_ref));
  REQUIRE(FAIR_AR_COMPARE(foo_ref, bar_ref, compare) > 0);
  REQUIRE(FAIR_AR_COMPARE(bar_ref, foo_ref, compare) < 0);
}
