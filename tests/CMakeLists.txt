# Tests

add_executable(test_queue queue.c)

target_include_directories(test_queue PRIVATE UNILIB_INCLUDE_DIR)
target_link_libraries(test_queue PRIVATE unilib)

add_test(NAME testunilib_queue COMMAND test_queue)
