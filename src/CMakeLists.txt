cmake_minimum_required(VERSION 3.19)
project(chacha C)

set(CMAKE_C_STANDARD 11)

add_executable(chacha main.c chacha.c chacha.h)