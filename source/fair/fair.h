#ifndef FAIR_FAIR_H
#define FAIR_FAIR_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FAIR_NODE_EMPTY 0
#define FAIR_NODE_FUNCTION 1

typedef void *(*fair_allocate)(void *state, size_t size);
typedef void (*fair_deallocate)(void *state, void *pointer);

typedef ptrdiff_t (*fair_read_fn)(void *state, ptrdiff_t size,
                                  char *dst);

struct fair_allocator {
  void           *state;
  fair_allocate   allocate;
  fair_deallocate deallocate;
};

struct fair_input_stream {
  void        *state;
  fair_read_fn read;
};

struct fair_syntax_tree {
  ptrdiff_t type;
  union {
    struct {
      char *name;
    } function;
  } node;
};

struct fair_syntax_tree fair_parse(struct fair_allocator    alloc,
                                   struct fair_input_stream in);

int fair_run(int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif
