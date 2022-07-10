cmake_minimum_required(VERSION 3.16)
set(NAME fair-integration-fetch-content)
project(${NAME} CXX)

include(FetchContent)
FetchContent_Declare(
  fair
  GIT_REPOSITORY https://github.com/automainint/fair.git
  GIT_TAG dev)
set(FAIR_ENABLE_TESTING OFF)
FetchContent_MakeAvailable(fair)

add_executable(${NAME})
target_sources(${NAME} PRIVATE main.cpp)
target_link_libraries(${NAME} PRIVATE fair::libfair)

enable_testing()
add_test(NAME ${NAME}-run COMMAND ${NAME})
set_tests_properties(${NAME}-run PROPERTIES TIMEOUT "15")
