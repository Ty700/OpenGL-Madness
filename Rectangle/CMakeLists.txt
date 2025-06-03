cmake_minimum_required(VERSION 3.12)
project(OpenGLApp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Fetch GLAD automatically
include(FetchContent)
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v0.1.36
)
FetchContent_MakeAvailable(glad)

add_executable(${PROJECT_NAME} rectangle.cpp)
add_subdirectory(shaders)

# Copy shader files to build directory
configure_file(${CMAKE_SOURCE_DIR}/shaders/vertex_shader.glsl ${CMAKE_BINARY_DIR}/vertex_shader.glsl COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/shaders/fragment_shader.glsl ${CMAKE_BINARY_DIR}/fragment_shader.glsl COPYONLY)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    glfw
    glad
)
