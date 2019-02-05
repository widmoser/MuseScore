cmake_minimum_required(VERSION 3.3)
project(Base64)

include_directories(include)
add_library(base64
        src/cdecode.c
        src/cencode.c)