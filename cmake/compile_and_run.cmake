set(TEST_FOLDER test)

macro(execute_and_check cmd_)
  execute_process(
    COMMAND ${cmd_}
    RESULT_VARIABLE result_)

  if(result_)
    message(FATAL_ERROR "${cmd_} failed")
  endif()
endmacro()

execute_and_check("${FAIR_EXE} -i \"${CMAKE_CURRENT_SOURCE_DIR}/${TEST_FOLDER}/${TEST_NAME}.fair\" -o \"${CMAKE_CURRENT_BINARY_DIR}/${TEST_FOLDER}/${TEST_NAME}.ll\"")
execute_and_check("llc --filetype=obj \"${CMAKE_CURRENT_BINARY_DIR}/${TEST_FOLDER}/${TEST_NAME}.ll\" -o \"${CMAKE_CURRENT_BINARY_DIR}/${TEST_FOLDER}/${TEST_NAME}.o\"")
execute_and_check("clang \"${CMAKE_CURRENT_BINARY_DIR}/${TEST_FOLDER}/${TEST_NAME}.o\" -o \"${CMAKE_CURRENT_BINARY_DIR}/${TEST_FOLDER}/${TEST_NAME}\"")
execute_and_check("${CMAKE_CURRENT_BINARY_DIR}/${TEST_FOLDER}/${TEST_NAME}")
