cmake_minimum_required(VERSION 3.8)
project(OpenGL_Learning)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCL)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

if(NOT OPENCL_FOUND)
set(OpenCL_INCLUDE_DIRS )
set(OpenCL_LIBRARIES )
endif()

include_directories(include/)
include_directories(${OpenCL_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${glfw_INCLUDE_DIRS})

set(SOURCE_FILES src/main.cpp src/glad.c)

add_executable(OpenGL_Learning ${SOURCE_FILES})
target_link_libraries(OpenGL_Learning ${OpenCL_LIBRARIES} ${OpenGL_LIBRARIES} glfw dl)
