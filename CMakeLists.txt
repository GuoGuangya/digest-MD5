cmake_minimum_required(VERSION 3.6)
project(untitled2 C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled2 main.c md5.c md5.h md5_digest.h md5_digest.c)
