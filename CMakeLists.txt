cmake_minimum_required(VERSION 3.17)
project(unilib C)

set(CMAKE_C_STANDARD 99)

add_library(uniqueue src/queue.h src/queue.c)
add_library(unistring src/string.c src/string.h)
