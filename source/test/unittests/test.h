#ifndef FAIR_TEST_H
#define FAIR_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#ifdef _MSC_VER
#  pragma section(".CRT$XCU", read)
#  define ON_START_2(f, p)                                         \
    static void f(void);                                           \
    __declspec(allocate(".CRT$XCU")) void (*f##_)(void) = f;       \
    __pragma(comment(linker, "/include:" p #f "_")) static void f( \
        void)
#  ifdef _WIN64
#    define ON_START(f) ON_START_2(f, "")
#  else
#    define ON_START(f) ON_START_2(f, "_")
#  endif
#else
#  define ON_START(f)                                 \
    static void f(void) __attribute__((constructor)); \
    static void f(void)
#endif

#define FAIR_TESTS_SIZE_LIMIT 0x1000
#define FAIR_TEST_STRING_SIZE 0x100

typedef void (*fair_test_report)(ptrdiff_t, bool);
typedef void (*fair_test_function)(ptrdiff_t, fair_test_report);

struct fair_test_case {
  char               test_name[FAIR_TEST_STRING_SIZE];
  fair_test_function test_fn;
  bool               test_status;
};

struct fair_tests_list {
  ptrdiff_t             size;
  struct fair_test_case tests[FAIR_TESTS_SIZE_LIMIT];
};

extern struct fair_tests_list fair_tests_list;

#define FAIR_TEST_CONCAT(a, b) a##b
#define FAIR_TEST_CONCAT2(a, b) FAIR_TEST_CONCAT(a, b)

#define TEST(name)                                  \
  static void FAIR_TEST_CONCAT2(fair_test_run_, __LINE__)( \
      ptrdiff_t, fair_test_report);                        \
  ON_START(FAIR_TEST_CONCAT2(fair_test_case_, __LINE__)) { \
    ptrdiff_t n = fair_tests_list.size;                    \
    fair_tests_list.size++;                                \
    fair_tests_list.tests[n].test_fn = FAIR_TEST_CONCAT2(  \
        fair_test_run_, __LINE__);                         \
    strcpy(fair_tests_list.tests[n].test_name, name);      \
    fair_tests_list.tests[n].test_status = true;           \
  }                                                        \
  static void FAIR_TEST_CONCAT2(fair_test_run_, __LINE__)( \
      ptrdiff_t        fair_test_index_,                   \
      fair_test_report fair_test_report_)

#define REQUIRE(ok) fair_test_report_(fair_test_index_, (ok))

#ifdef __cplusplus
}
#endif

#endif