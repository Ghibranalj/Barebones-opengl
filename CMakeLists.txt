cmake_minimum_required(VERSION 3.7)

project(OPENGL VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_BUILD_TYPE Debug)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

file(GLOB_RECURSE SRC_FILES "src/*.cpp")

include_directories(src)

message(STATUS SRC_FILES: ${SRC_FILES})

add_executable(GAME ${SRC_FILES})
target_link_libraries(GAME glfw OpenGL::GL GLEW::GLEW)


file(COPY res DESTINATION ${CMAKE_BINARY_DIR})

# add run target
add_custom_target(run
    COMMAND GAME
    DEPENDS GAME
)
