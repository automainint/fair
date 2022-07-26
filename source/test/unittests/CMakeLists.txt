target_sources(
  ${FAIR_EXE}
    PRIVATE
      main.test.c fair.test.c
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/test.h>)
