cmake_minimum_required(VERSION 3.19)

project(unilib
        VERSION 0.1.0
        DESCRIPTION "C library for university students."
        LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

set(UNILIB_INCLUDE_DIR "include/unilib")
set(UNILIB_SRC_DIR "src")

set(UNILIB_HEADERS
        "${UNILIB_INCLUDE_DIR}/dequeue.h")
set(UNILIB_SRC
        "${UNILIB_SRC_DIR}/dequeue.c")

add_library(unilib STATIC ${UNILIB_HEADERS} ${UNILIB_SRC})

target_include_directories(unilib PUBLIC "${UNILIB_INCLUDE_DIR}")

enable_testing()
add_subdirectory(tests)
