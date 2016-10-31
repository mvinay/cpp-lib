project("cpp-lib")

add_executable(vec-tests VectorTests.cpp)
target_link_libraries(vec-tests ${GTEST_LIBRARIES} pthread cpp_lib)

add_test(tests ${CMAKE_BINARY_DIR}/bin/vec-tests)
