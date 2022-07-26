#ifndef FAIR_MEMORY_H
#define FAIR_MEMORY_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void *(*fair_allocate_fn)(void *state, size_t size);
typedef void (*fair_deallocate_fn)(void *state, void *pointer);

struct fair_allocator {
  void              *state;
  fair_allocate_fn   allocate;
  fair_deallocate_fn deallocate;
};

struct fair_allocator fair_alloc_default();

#ifdef __cplusplus
}
#endif

#endif
