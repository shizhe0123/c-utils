cmake_minimum_required(VERSION 3.15)
project(divide_conquer)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(./ SRC_FILES)

add_executable(divide_conquer ${SRC_FILES})