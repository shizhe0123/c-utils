cmake_minimum_required(VERSION 3.13)
project(clion_project C)

set(CMAKE_C_STANDARD 99)

add_executable(clion_project ../main.c ../sort_find.c ../vector.c)