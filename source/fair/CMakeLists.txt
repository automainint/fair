target_sources(
  ${FAIR_LIBRARY}
    PRIVATE
      fair.cpp
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/fair.h>)
