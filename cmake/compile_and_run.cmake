set(TEST_FOLDER test)

macro(execute_and_check)
  execute_process(
    COMMAND ${ARGN}
    RESULT_VARIABLE result_)

  if(result_)
    message(FATAL_ERROR "${ARGN} failed: ${result_}")
  endif()
endmacro()

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${TEST_FOLDER})
execute_and_check(${FAIR_EXE} -i ${SOURCE_DIR}/${TEST_NAME}.fair -o ${CMAKE_CURRENT_BINARY_DIR}/${TEST_FOLDER}/${TEST_NAME}.c)
execute_and_check(cc ${CMAKE_CURRENT_BINARY_DIR}/${TEST_FOLDER}/${TEST_NAME}.c -o ${CMAKE_CURRENT_BINARY_DIR}/${TEST_FOLDER}/${TEST_NAME}${CMAKE_EXECUTABLE_SUFFIX})
execute_and_check(${CMAKE_CURRENT_BINARY_DIR}/${TEST_FOLDER}/${TEST_NAME}${CMAKE_EXECUTABLE_SUFFIX})
