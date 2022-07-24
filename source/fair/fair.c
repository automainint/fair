#include "fair.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  bool        is_error;
  char const *input_file;
  char const *output_file;
} parsed_arguments;

parsed_arguments parse_arguments(int argc, char **argv) {
  parsed_arguments result = { .is_error    = false,
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

typedef struct {
  bool is_error;
  bool is_main;
} ast;

FILE *read_input(parsed_arguments args) {
  if (args.is_error)
    return NULL;
  return fopen(args.input_file, "r");
}

FILE *write_output(parsed_arguments args) {
  if (args.is_error)
    return NULL;
  return fopen(args.output_file, "w");
}

void close_file(FILE *f) {
  if (f != NULL)
    fclose(f);
}

ast parse_file(FILE *in) {
  ast result = { .is_error = false, .is_main = false };

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

int print_ast(ast data, FILE *out) {
  if (data.is_error || out == NULL)
    return 1;
  if (data.is_main) {
    fputs("int main(int argc, char **argv) {\n", out);
    fputs("  return 0;\n", out);
    fputs("}\n", out);
  }
  return 0;
}

int fair_run(int argc, char **argv) {
  parsed_arguments args = parse_arguments(argc, argv);

  FILE *in  = read_input(args);
  FILE *out = write_output(args);

  int status = print_ast(parse_file(in), out);

  close_file(in);
  close_file(out);
  return status;
}
