#include "fair.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fair_run(int argc, char **argv) {
  char const *input_file  = 0;
  char const *output_file = 0;

  for (int i = 0; i < argc; i++) {
    if (strcmp("-i", argv[i]) == 0 && i + 1 < argc)
      input_file = argv[++i];
    else if (strcmp("-o", argv[i]) == 0 && i + 1 < argc)
      output_file = argv[++i];
  }

  FILE *in  = fopen(input_file, "r");

  if (!in)
    return 1;

  FILE *out = fopen(output_file, "w");

  if (!out) {
    fclose(in);
    return 1;
  }

  char buf[1024] = { '\0' };

  int n = fread(buf, 1, 1023, in);

  if (n < 0) {
    fclose(in);
    fclose(out);
    return 1;
  }

  if (strstr(buf, "fn main") != 0) {
    fputs("int main(int argc, char **argv) {\n", out);
    fputs("  return 0;\n", out);
    fputs("}\n", out);
  }

  fclose(in);
  fclose(out);
  return 0;
}
