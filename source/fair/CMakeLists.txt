target_sources(
  ${FAIR_LIBRARY}
    PRIVATE
      fair.c memory.c array_ref.c dynamic_array.c
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/fair.h>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/dynamic_array.h>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/memory.h>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/array_ref.h>)
