cmake_minimum_required(VERSION 3.13)
project(clion_project C)

set(CMAKE_C_STANDARD 99)

aux_source_directory(../ DIR_SRCS)

add_executable(clion_project ${DIR_SRCS})