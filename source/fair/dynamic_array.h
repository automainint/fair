#ifndef FAIR_DYNAMIC_ARRAY_H
#define FAIR_DYNAMIC_ARRAY_H

#include "memory.h"

#ifdef __cplusplus
extern "C" {
#endif

struct fair_da_void {
  ptrdiff_t             capacity;
  ptrdiff_t             size;
  void                 *values;
  struct fair_allocator alloc;
};

void fair_da_init(struct fair_da_void *array, ptrdiff_t element_size,
                  ptrdiff_t size, struct fair_allocator alloc);

void fair_da_resize(struct fair_da_void *array,
                    ptrdiff_t element_size, ptrdiff_t size);

/*  Declare dynamic array.
 */
#define FAIR_DA(name_, type_)       \
  struct {                          \
    ptrdiff_t             capacity; \
    ptrdiff_t             size;     \
    type_                *values;   \
    struct fair_allocator alloc;    \
  } name_

/*  Declare dynamic array type.
 */
#define FAIR_DA_TYPE(name_, element_type_) \
  struct name_ {                           \
    ptrdiff_t             capacity;        \
    ptrdiff_t             size;            \
    element_type_        *values;          \
    struct fair_allocator alloc;           \
  }

/*  Initialize dynamic array variable.
 */
#define FAIR_DA_INIT(array_, size_, alloc_)     \
  fair_da_init((struct fair_da_void *) &array_, \
               sizeof(array_.values[0]), (size_), (alloc_))

/*  Declare and initialize dynamic array.
 */
#define FAIR_DA_CREATE(name_, type_, size_)                   \
  FAIR_DA(name_, type_);                                      \
  fair_da_init((struct fair_da_void *) &name_, sizeof(type_), \
               (size_), fair_alloc_default())

/*  Destroy dynamic array.
 */
#define FAIR_DA_DESTROY(array_)                       \
  {                                                   \
    if ((array_).values != NULL)                      \
      (array_).alloc.deallocate((array_).alloc.state, \
                                (array_).values);     \
  }

/*  Resize dynamic array.
 */
#define FAIR_DA_RESIZE(array_, size_)               \
  fair_da_resize((struct fair_da_void *) &(array_), \
                 sizeof((array_).values[0]), size_)

/*  Append a value to dynamic array.
 */
#define FAIR_DA_APPEND(array_, value_)                \
  {                                                   \
    ptrdiff_t const fair_index_back_ = (array_).size; \
    FAIR_DA_RESIZE((array_), fair_index_back_ + 1);   \
    if (fair_index_back_ < (array_).size)             \
      (array_).values[fair_index_back_] = (value_);   \
  }

/*  Insert a value into dynamic array.
 */
#define FAIR_DA_INSERT(array_, index_, value_)                   \
  {                                                              \
    ptrdiff_t const fair_index_back_ = (array_).size;            \
    ptrdiff_t const fair_indert_n_   = (index_);                 \
    FAIR_DA_RESIZE((array_), fair_index_back_ + 1);              \
    if (fair_index_back_ + 1 == (array_).size) {                 \
      for (ptrdiff_t fair_i_ = fair_index_back_;                 \
           fair_i_ > fair_indert_n_; fair_i_--)                  \
        (array_).values[fair_i_] = (array_).values[fair_i_ - 1]; \
      (array_).values[fair_indert_n_] = (value_);                \
    }                                                            \
  }

/*  Erase a value from dynamic array.
 */
#define FAIR_DA_ERASE(array_, index_)                           \
  {                                                             \
    for (ptrdiff_t i_ = (index_) + 1; i_ < (array_).size; i_++) \
      (array_).values[i_ - 1] = (array_).values[i_];            \
    FAIR_DA_RESIZE((array_), (array_).size - 1);                \
  }

#ifdef __cplusplus
}
#endif

#endif
