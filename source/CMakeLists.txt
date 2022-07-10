add_subdirectory(fair)
add_subdirectory(standalone)

if(FAIR_ENABLE_TESTING)
  add_subdirectory(test)
endif()
