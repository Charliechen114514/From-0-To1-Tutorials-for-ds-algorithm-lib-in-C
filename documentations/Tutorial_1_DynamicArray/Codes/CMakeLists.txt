cmake_minimum_required(VERSION 3.5.0)
project(DynamicArray VERSION 0.1.0 LANGUAGES C)

add_executable(DynamicArray main.c DynamicArray/sources/DynamicArray.c)
target_include_directories(DynamicArray PRIVATE DynamicArray/include)


