function(cxx_test name)
  add_executable(${name} "tests/${name}.cc")
  target_link_libraries(${name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tests)
  foreach(lib ${ARGN})
    target_link_libraries(${name} PUBLIC ${lib})
  endforeach()
  add_test(NAME ${name} COMMAND "$<TARGET_FILE:${name}>")
endfunction()