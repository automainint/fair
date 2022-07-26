#include "memory.h"

#include <stdlib.h>

static void *allocate(void *_, size_t size) {
  return malloc(size);
}

static void deallocate(void *_, void *pointer) {
  free(pointer);
}

struct fair_allocator fair_alloc_default() {
  struct fair_allocator alloc = {
    .state = NULL,
    .allocate = allocate,
    .deallocate = deallocate
  };
  
  return alloc;
}
