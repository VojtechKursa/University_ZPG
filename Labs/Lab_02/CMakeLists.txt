cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()



project ("Lab_02")



# Add source to this project's executable.
add_executable (main
	"main.cpp"
  "Application.cpp" "Application.h"
  "Renderer.cpp" "Renderer.h"
  "ShaderProgram.cpp" "ShaderProgram.h"
  "Shader.cpp" "Shader.h"
  "VertexShader.cpp" "VertexShader.h"
  "FragmentShader.cpp" "FragmentShader.h"
  "Shape.cpp" "Shape.h"
  "Triangle.cpp" "Triangle.h"
  "Rectangle.cpp" "Rectangle.h"
  "ShapeFactory.cpp" "ShapeFactory.h"
  "VAO.cpp" "VAO.h"
  "VBO.cpp" "VBO.h"
  )



if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET main PROPERTY CXX_STANDARD 20)
endif()



# Libraries

# GLM
target_include_directories(main PUBLIC ../../Libraries-src/glm/)


# GLFW
add_subdirectory(../../Libraries-src/glfw ../../Libraries-src/glfw)
add_dependencies(main glfw)

target_include_directories(main PUBLIC ../../Libraries-src/glfw/include)

target_link_libraries(main glfw)


# OpenGL
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)

target_include_directories(main PUBLIC ${OPENGL_INCLUDE_DIRS})

target_link_libraries(main ${OPENGL_LIBRARIES})


# GLU
# find_package(GLU REQUIRED)

# target_include_directories(main PUBLIC ${GLU_INCLUDE_DIRS})

# target_link_libraries(main ${GLU_LIBRARY})


# GLEW
target_include_directories(main PUBLIC ../../Libraries-src/glew/include)

target_link_directories(main PUBLIC ../../Libraries-src/glew/lib)
target_link_libraries(main GLEW)
