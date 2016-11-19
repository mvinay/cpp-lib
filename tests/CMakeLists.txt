project("cpp-lib")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_subdirectory(lists)
add_subdirectory(stack)
add_subdirectory(queue)
add_subdirectory(map)
