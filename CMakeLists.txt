cmake_minimum_required(VERSION 3.13)
project(sokoban_proj)

set(CMAKE_CXX_STANDARD 11)


include_directories(/home/akuznetsov/libtcod/include/ /home/akuznetsov/sokoban_proj/cmake-build-debug/)
link_directories(/home/akuznetsov/libtcod/ /home/akuznetsov/sokoban_proj/cmake-build-debug/)


add_executable(sokoban_proj main.cpp cmake-build-debug/TwoDimArray.cpp cmake-build-debug/TwoDimArray.h)

target_link_libraries(sokoban_proj -ltcod -ltcodxx)