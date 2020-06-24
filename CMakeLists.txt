
cmake_minimum_required(VERSION 3.7)


project(OPENGL VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")



add_subdirectory(vendor)

find_package(OpenGL REQUIRED)


add_executable(GAME main.cpp)

target_link_libraries(GAME glfw OpenGL::GL glad)

