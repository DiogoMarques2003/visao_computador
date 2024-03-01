cmake_minimum_required(VERSION 3.27)
project(projeto C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(projeto
        main.c
        vc.c
        vc.h)
