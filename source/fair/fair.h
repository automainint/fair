#ifndef FAIR_FAIR_H
#define FAIR_FAIR_H

#ifdef __cplusplus
namespace fair {
  [[nodiscard]] auto run(int argc, char **argv) -> int;
}

extern "C" {
#endif
  int fair_run(int argc, char **argv);
#ifdef __cplusplus
}
#endif

#endif
