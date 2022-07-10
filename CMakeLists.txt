cmake_minimum_required(VERSION 3.16)

option(FAIR_ENABLE_LIBRARY "Enable library" ON)
option(FAIR_ENABLE_STANDALONE "Enable standalone" ON)
option(FAIR_ENABLE_TESTING "Enable testing" ON)

set(FAIR_PROJECT fair)
set(FAIR_LIBRARY fair)
set(FAIR_EXE fairc)
set(FAIR_TARGETS fair-targets)
set(FAIR_UNITTESTS fair-unittests)

if(NOT DEFINED CMAKE_BUILD_PARALLEL_LEVEL)
  set(CMAKE_BUILD_PARALLEL_LEVEL 3)
endif()

project(
  ${FAIR_PROJECT}
  VERSION 0.1.1
  DESCRIPTION "Compiler experiments"
  LANGUAGES CXX)

if(FAIR_ENABLE_LIBRARY OR FAIR_ENABLE_STANDALONE OR FAIR_ENABLE_TESTING)
  find_package(Threads REQUIRED)

  add_library(${FAIR_LIBRARY} STATIC)
  add_library(${FAIR_PROJECT}::${FAIR_LIBRARY} ALIAS ${FAIR_LIBRARY})
  target_include_directories(
    ${FAIR_LIBRARY} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>)
  target_compile_features(${FAIR_LIBRARY} PUBLIC cxx_std_20)
  target_link_libraries(${FAIR_LIBRARY} PUBLIC Threads::Threads)
endif()

if(FAIR_ENABLE_STANDALONE OR FAIR_ENABLE_TESTING)
  add_executable(${FAIR_EXE})
  add_executable(${FAIR_PROJECT}::${FAIR_EXE} ALIAS ${FAIR_EXE})
  target_compile_features(${FAIR_EXE} PRIVATE cxx_std_20)
  target_link_libraries(${FAIR_EXE} PRIVATE ${FAIR_LIBRARY})

  if(FAIR_ENABLE_TESTING)
    target_compile_definitions(${FAIR_EXE} PRIVATE FAIR_ENABLE_TESTING)
  endif()
endif()

enable_testing()

if(FAIR_ENABLE_TESTING)
  find_package(Catch2 QUIET)

  if(NOT Catch2_FOUND)
    include(FetchContent)

    FetchContent_Declare(
      Catch2
      GIT_REPOSITORY https://github.com/catchorg/Catch2.git
      GIT_TAG v2.13.9)

    FetchContent_MakeAvailable(Catch2)
  endif()

  target_link_libraries(${FAIR_EXE} PRIVATE Catch2::Catch2)

  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(
      ${FAIR_LIBRARY} PUBLIC
      -fsanitize=undefined,address
      --coverage -O0 -g)
    target_link_options(
      ${FAIR_LIBRARY} PUBLIC
      -fsanitize=undefined,address
      --coverage)
  endif()

  add_test(
    NAME ${FAIR_UNITTESTS}
    COMMAND ${FAIR_EXE} --test)

  set_tests_properties(
    ${FAIR_UNITTESTS}
    PROPERTIES
    TIMEOUT "15")

  add_test(
    NAME empty
    COMMAND ${CMAKE_COMMAND} -D FAIR_EXE=$<TARGET_FILE:${FAIR_EXE}> -D SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/test -D TEST_NAME=empty -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/compile_and_run.cmake)

  set_tests_properties(
    empty
    PROPERTIES
    TIMEOUT "15"
    WILL_FAIL TRUE)

  add_test(
    NAME blank
    COMMAND ${CMAKE_COMMAND} -D FAIR_EXE=$<TARGET_FILE:${FAIR_EXE}> -D SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/test -D TEST_NAME=blank -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/compile_and_run.cmake)

  set_tests_properties(
    blank
    PROPERTIES
    TIMEOUT "15")
endif()

add_subdirectory(source)

if(FAIR_ENABLE_LIBRARY OR FAIR_ENABLE_STANDALONE)
  include(GNUInstallDirs)

  if(FAIR_ENABLE_LIBRARY)
    file(
      GLOB_RECURSE headers_
      RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/source/fair
      ${CMAKE_CURRENT_SOURCE_DIR}/source/fair/*.h)

    foreach(path_ ${headers_})
      get_filename_component(dir_ "${path_}" DIRECTORY)

      install(
        FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/fair/${path_}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fair/${dir_})
    endforeach()

    unset(headers_)
    unset(path_)
    unset(dir_)

    install(
      TARGETS ${FAIR_LIBRARY}
      EXPORT ${FAIR_TARGETS}
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
      INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
  endif()

  if(FAIR_ENABLE_STANDALONE)
    install(
      TARGETS ${FAIR_EXE}
      EXPORT ${FAIR_TARGETS}
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
  endif()

  install(
    EXPORT ${FAIR_TARGETS}
    FILE ${FAIR_TARGETS}.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

  export(
    EXPORT ${FAIR_TARGETS}
    FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${FAIR_TARGETS}.cmake"
    NAMESPACE ${PROJECT_NAME}::)

  include(CMakePackageConfigHelpers)

  string(TOLOWER ${PROJECT_NAME} project_lower_)

  configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${project_lower_}-config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

  write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${project_lower_}-config-version.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY AnyNewerVersion)

  install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${project_lower_}-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${project_lower_}-config-version.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

  unset(project_lower_)
endif()
