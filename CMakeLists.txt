cmake_minimum_required(VERSION 3.7)

project(OPENGL VERSION 1.0.0)

if (POLICY CMP0072)
  cmake_policy (SET CMP0072 NEW)
endif(POLICY CMP0072)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DRELEASE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
else()
    add_definitions(-DDEBUG)
   set(CMAKE_BUILD_TYPE Debug)
endif()


find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)
find_package(assimp REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

set(INCLUDE_DIRS  "src")
add_subdirectory(vendor)

file(GLOB_RECURSE SRCPP_FILES "src/*.cpp")
file(GLOB_RECURSE SRC_FILES "src/*.c")

include_directories(${INCLUDE_DIRS})
add_executable(GAME ${SRC_FILES} ${SRCPP_FILES})

target_link_libraries(GAME glfw OpenGL::GL GLEW::GLEW glm::glm assimp)

#glob everything in res
add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/res
        ${PROJECT_BINARY_DIR}/res
        COMMENT "Copying resources into binary directory")

add_dependencies(GAME copy_resources)# add run target
add_custom_target(run
    COMMAND GAME || true
    DEPENDS GAME
    COMMENT "=== Running GAME ==="
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)


set(valgrind_supp "${CMAKE_CURRENT_SOURCE_DIR}/valgrind.supp")
set(valgrind_cmd valgrind --leak-check=full --log-file=valgrind-out.txt --suppressions=${valgrind_supp} --track-origins=yes)
add_custom_target(valgrind
    COMMAND ${valgrind_cmd} ./GAME
    DEPENDS GAME
    COMMENT "=== Running GAME under valgrind ==="
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
