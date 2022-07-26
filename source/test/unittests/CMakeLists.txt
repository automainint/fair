target_sources(
  ${FAIR_EXE}
    PRIVATE
      main.test.c array_ref.test.c fair.test.c
      dynamic_array.test.c
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/test.h>)
