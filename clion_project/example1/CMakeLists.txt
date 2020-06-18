cmake_minimum_required(VERSION 3.15)
project(UThash C)

set(CMAKE_C_STANDARD 99)

add_executable(UThash main.c
        headerfile/header.h
        headerfile/data_type_define.h
        uthash/utarray.h
        uthash/uthash.h
        uthash/utlist.h
        uthash/utringbuffer.h
        uthash/utstack.h
        uthash/utstring.h
        )