#include "fair.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct parsed_arguments {
  bool        is_error;
  char const *input_file;
  char const *output_file;
};

struct parsed_arguments parse_arguments(int argc, char **argv) {
  struct parsed_arguments result = { .is_error    = false,
                                     .input_file  = NULL,
                                     .output_file = NULL };

  for (int i = 0; i < argc; i++) {
    if (strcmp("-i", argv[i]) == 0 && i + 1 < argc) {
      if (result.input_file != NULL)
        result.is_error = true;
      result.input_file = argv[++i];
    } else if (strcmp("-o", argv[i]) == 0 && i + 1 < argc) {
      if (result.output_file != NULL)
        result.is_error = true;
      result.output_file = argv[++i];
    }
  }

  if (result.input_file == NULL)
    result.is_error = true;
  if (result.output_file == NULL)
    result.is_error = true;
  return result;
}

struct syntax_tree {
  bool is_error;
  bool is_main;
};

FILE *read_input(struct parsed_arguments args) {
  if (args.is_error)
    return NULL;
  return fopen(args.input_file, "r");
}

FILE *write_output(struct parsed_arguments args) {
  if (args.is_error)
    return NULL;
  return fopen(args.output_file, "w");
}

void close_file(FILE *f) {
  if (f != NULL)
    fclose(f);
}

struct syntax_tree parse_file(FILE *in) {
  struct syntax_tree result = { .is_error = false, .is_main = false };

  if (in == NULL)
    result.is_error = true;
  else {
    char buf[1024] = { '\0' };
    fread(buf, 1, 1023, in);

    if (strstr(buf, "fn main") != 0)
      result.is_main = true;
  }

  return result;
}

int print_c(struct syntax_tree data, FILE *out) {
  if (data.is_error || out == NULL)
    return 1;
  if (data.is_main) {
    fputs("int main(int argc, char **argv) {\n", out);
    fputs("  return 0;\n", out);
    fputs("}\n", out);
  }
  return 0;
}

struct fair_syntax_tree fair_parse(struct fair_allocator    alloc,
                                   struct fair_input_stream in) {
  char      buf[0x1000] = { 0 };
  ptrdiff_t size        = 0;

  for (;;) {
    ptrdiff_t n = in.read(in.state, 256, buf + size);
    if (n == 0)
      break;
    size += n;
  }

  if (memcmp("fn ", buf, 3) == 0) {
    char     *name     = buf + 3;
    char     *name_end = strstr(name, "(");
    ptrdiff_t name_len = name_end - name;

    struct fair_syntax_tree tree = {
      .type               = FAIR_NODE_FUNCTION,
      .node.function.name = (char *) alloc.allocate(alloc.state,
                                                    name_len + 1)
    };

    memset(tree.node.function.name, 0, name_len + 1);
    memcpy(tree.node.function.name, name, name_len);

    return tree;
  }

  struct fair_syntax_tree tree = { .type = FAIR_NODE_EMPTY };
  return tree;
}

int fair_run(int argc, char **argv) {
  struct parsed_arguments args = parse_arguments(argc, argv);

  FILE *in  = read_input(args);
  FILE *out = write_output(args);

  int status = print_c(parse_file(in), out);

  close_file(in);
  close_file(out);
  return status;
}
