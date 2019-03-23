cmake_minimum_required(VERSION 2.8)
project (program2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(../lib/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)

include_directories(../lib/glfw/include)
include_directories(../lib/glad/include)
include_directories(../lib/csci441/include)

set(LAB Program2)
add_executable(${LAB} main.cpp ../lib/glad/src/glad.c Vertex.h Face.h ObjReader.h CameraMover.h)
target_link_libraries(${LAB} glfw ${GLFW_LIBRARIES})

