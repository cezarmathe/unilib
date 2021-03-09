# Tests

add_executable(test_dequeue dequeue.c)

target_include_directories(test_dequeue PRIVATE UNILIB_INCLUDE_DIR)
target_link_libraries(test_dequeue PRIVATE unilib)

add_test(NAME test_dequeue COMMAND test_dequeue)
