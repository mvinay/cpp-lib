project("cpp-lib")

add_executable(stack-test StackTests.cpp)

target_link_libraries(stack-test ${GTEST_LIBRARIES} pthread )

add_test(ds-tests ${CMAKE_BINARY_DIR}/bin/stack-test)
