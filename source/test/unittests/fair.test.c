#include "../../fair/fair.h"
#include "test.h"

#include <stdlib.h>

struct string_state {
  ptrdiff_t   offset;
  char const *string;
};

static ptrdiff_t read_string(void *data, ptrdiff_t size, char *dst) {
  struct string_state *state  = (struct string_state *) data;
  ptrdiff_t            copied = 0;
  while (copied < size &&
         state->string[state->offset + copied] != '\n')
    copied++;
  if (copied > 0) {
    memcpy(dst, state->string + state->offset, copied);
    state->offset += copied;
  }
  return copied;
}

static struct fair_input_stream wrap(char const *text) {
  struct string_state *state = (struct string_state *) malloc(
      sizeof(struct string_state));

  memset(state, 0, sizeof *state);
  state->offset = 0;
  state->string = text;

  struct fair_input_stream stream = { .state = state,
                                      .read  = read_string };

  return stream;
}

static void *allocate(void *_, size_t size) {
  return malloc(size);
}

static void deallocate(void *_, void *pointer) {
  free(pointer);
}

static struct fair_allocator alloc() {
  struct fair_allocator a = { .state      = NULL,
                              .allocate   = allocate,
                              .deallocate = deallocate };
  return a;
}

TEST("syntax tree empty") {
  struct fair_input_stream in   = wrap("");
  struct fair_syntax_tree  tree = fair_parse(alloc(), in);

  REQUIRE(tree.type == FAIR_NODE_EMPTY);

  free(in.state);
}

TEST("syntax tree function") {
  struct fair_input_stream in   = wrap("fn foo() { }");
  struct fair_syntax_tree  tree = fair_parse(alloc(), in);

  REQUIRE(tree.type == FAIR_NODE_FUNCTION);
  REQUIRE(strcmp("foo", tree.node.function.name) == 0);

  free(in.state);
  free(tree.node.function.name);
}