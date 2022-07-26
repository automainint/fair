#ifndef FAIR_ARRAY_REF_H
#define FAIR_ARRAY_REF_H

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct fair_ar_ref_void {
  ptrdiff_t size;
  void     *values;
};

typedef int (*fair_ar_compare_fn)(void const *left,
                                  void const *right);

bool fair_ar_equal_bytes(ptrdiff_t left_element_size,
                         ptrdiff_t left_size, void const *left_data,
                         ptrdiff_t   right_element_size,
                         ptrdiff_t   right_size,
                         void const *right_data);

int fair_ar_compare(ptrdiff_t left_element_size, ptrdiff_t left_size,
                    void const *left_data,
                    ptrdiff_t   right_element_size,
                    ptrdiff_t right_size, void const *right_data,
                    fair_ar_compare_fn compare);

#define FAIR_AR(name_, type_) \
  struct {                    \
    ptrdiff_t size;           \
    type_    *values;         \
  } name_

#define FAIR_AR_EQUAL(left_, right_)                              \
  fair_ar_equal_bytes(sizeof((left_).values[0]), (left_).size,    \
                      (left_).values, sizeof((right_).values[0]), \
                      (right_).size, (right_).values)

#define FAIR_AR_COMPARE(left_, right_, compare_)              \
  fair_ar_compare(sizeof((left_).values[0]), (left_).size,    \
                  (left_).values, sizeof((right_).values[0]), \
                  (right_).size, (right_).values,             \
                  (fair_ar_compare_fn) (compare_))

#ifdef __cplusplus
}
#endif

#endif
