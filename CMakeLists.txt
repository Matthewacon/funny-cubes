cmake_minimum_required(VERSION 3.8)
project(OpenGL_Learning)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} include/)
link_libraries(${OpenCL_LIBRARIES} ${OpenGL_LIBRARIES} ${GLFW_LIBRARIES})
set(SOURCE_FILES src/main.cpp src/glad.c src/stb_image.h src/ogl_utils.hpp)
add_executable(OpenGL_Learning ${SOURCE_FILES})

target_include_directories(OpenGL_Learning PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} include/)
target_link_libraries(OpenGL_Learning OpenCL::OpenCL OpenGL glfw dl)
