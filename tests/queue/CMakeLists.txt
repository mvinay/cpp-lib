project("cpp-lib")

add_executable(queue-test QueueTests.cpp)

target_link_libraries(queue-test ${GTEST_LIBRARIES} pthread )

add_test(ds-tests ${CMAKE_BINARY_DIR}/bin/queue-test)
