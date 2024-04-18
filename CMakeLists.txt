cmake_minimum_required(VERSION 3.11)

project(crypto)

set(CMAKE_C_STANDARD 17)

add_executable(rsa
src/rsa.c
src/utils.h
)

add_executable(djikstra
src/djikstra.c)