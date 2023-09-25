cmake_minimum_required(VERSION 3.22)

project(Lab_01)



# Executable
add_executable(main Lab_01.cpp)



# Libraries

# GLM
include_directories(../../Libraries/glm/)


# GLFW
add_subdirectory(../../Libraries/glfw ../../Libraries/glfw)
add_dependencies(main glfw)

include_directories(../../Libraries/glfw/include)

target_link_libraries(main glfw)


# OpenGL
find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})

target_link_libraries(main ${OPENGL_LIBRARIES})


# GLU
# find_package(GLU REQUIRED)

# include_directories(${GLU_INCLUDE_DIRS})

# target_link_libraries(main ${GLU_LIBRARY})