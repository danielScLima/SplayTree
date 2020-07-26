cmake_minimum_required(VERSION 3.12)
project(Program VERSION 1.0.0)

add_library(
	libsplaytree
	nodeofsplaytree.h
	splaytree.h
	splaytree.cpp
)

add_executable(program program.cpp)

target_link_libraries(program PRIVATE libsplaytree)
