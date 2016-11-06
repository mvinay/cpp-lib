project("cpp-lib")

add_executable(arr-tests ArrayListTests.cpp)
target_link_libraries(arr-tests ${GTEST_LIBRARIES} pthread )

add_test(tests ${CMAKE_BINARY_DIR}/bin/arr-tests)
