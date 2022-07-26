#include "../../fair/fair.h"
#include "../../fair/array_ref.h"

#define FAIR_TEST_FILE fair
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
         state->string[state->offset + copied] != '\0')
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

TEST("syntax tree empty") {
  struct fair_input_stream in  = wrap("");
  struct fair_syntax_tree tree = fair_parse(fair_alloc_default(), in);

  REQUIRE(tree.size == 0);

  free(in.state);
  FAIR_SYNTAX_TREE_DESTROY(tree);
}

TEST("syntax tree function") {
  struct fair_input_stream in  = wrap("fn foo() { }");
  struct fair_syntax_tree tree = fair_parse(fair_alloc_default(), in);

  FAIR_AR(s_foo, char) = { .size = 3, .values = "foo" };

  REQUIRE(tree.size == 1);
  REQUIRE(tree.values[0].type == FAIR_NODE_FUNCTION);
  REQUIRE(FAIR_AR_EQUAL(s_foo, tree.values[0].function.name));

  free(in.state);
  FAIR_SYNTAX_TREE_DESTROY(tree);
}