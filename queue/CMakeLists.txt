cmake_minimum_required(VERSION 3.5)
project(iterator VERSION 1.0.0)

add_subdirectory(lib)

add_executable(app "main.cpp")

target_link_libraries(app PRIVATE lib)