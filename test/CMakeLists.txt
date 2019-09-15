message("${project_BIN}")
add_executable(test test_bootstrap.cpp test_financial.cpp)
target_link_libraries(test gtest_main ${project_LIB})

