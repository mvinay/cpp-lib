project("cpp-lib")

add_executable(arr-tests ArrayListTests.cpp)
add_executable(ll-tests LinkedListTests.cpp)

target_link_libraries(arr-tests ${GTEST_LIBRARIES} pthread )
target_link_libraries(ll-tests ${GTEST_LIBRARIES} pthread )

add_test(ds-tests ${CMAKE_BINARY_DIR}/bin/arr-tests)
add_test(ds-tests ${CMAKE_BINARY_DIR}/bin/ll-tests)
