project("cpp-lib")

add_executable(hashmap-test HashMapTests.cpp)

target_link_libraries(hashmap-test ${GTEST_LIBRARIES} pthread )

add_test(ds-tests ${CMAKE_BINARY_DIR}/bin/hashmap-test)
