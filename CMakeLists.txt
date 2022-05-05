cmake_minimum_required(VERSION 3.21)
project(TAKUZU C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(TAKUZU
        functions.c
        functions.h
        main.c)
