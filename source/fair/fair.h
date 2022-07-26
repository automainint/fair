#ifndef FAIR_FAIR_H
#define FAIR_FAIR_H

#include "dynamic_array.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FAIR_NODE_EMPTY 0
#define FAIR_NODE_FUNCTION 1

typedef ptrdiff_t (*fair_read_fn)(void *state, ptrdiff_t size,
                                  char *dst);

struct fair_input_stream {
  void        *state;
  fair_read_fn read;
};

struct fair_syntax_tree_node {
  ptrdiff_t type;
  union {
    struct {
      FAIR_DA(name, char);
    } function;
  };
};

FAIR_DA_TYPE(fair_syntax_tree, struct fair_syntax_tree_node);

#define FAIR_SYNTAX_TREE_DESTROY(tree_)                            \
  {                                                                \
    for (ptrdiff_t fair_i_ = 0; fair_i_ < (tree_).size; fair_i_++) \
      if ((tree_).values[fair_i_].type == FAIR_NODE_FUNCTION) {    \
        FAIR_DA_DESTROY((tree_).values[fair_i_].function.name);    \
      }                                                            \
    FAIR_DA_DESTROY((tree_));                                      \
  }

struct fair_syntax_tree fair_parse(struct fair_allocator    alloc,
                                   struct fair_input_stream in);

int fair_run(int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif
