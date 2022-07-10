cmake_minimum_required(VERSION 3.16)
set(NAME fair-integration-find-package)
project(${NAME})

find_package(fair REQUIRED)

add_executable(${NAME})
target_sources(${NAME} PRIVATE main.cpp)
target_link_libraries(${NAME} PRIVATE fair::fair)
install(TARGETS ${NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
