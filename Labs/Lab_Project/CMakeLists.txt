cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()



project ("ZPG_Project")

set(CMAKE_BUILD_TYPE Debug)



# Add source to this project's executable.
file(GLOB SRC_FILES
  "${PROJECT_SOURCE_DIR}/*.h" "${PROJECT_SOURCE_DIR}/*.cpp"
  "${PROJECT_SOURCE_DIR}/Interfaces/*.h"
  "${PROJECT_SOURCE_DIR}/Model/*.h" "${PROJECT_SOURCE_DIR}/Model/*.cpp"
  "${PROJECT_SOURCE_DIR}/Model/Models/*.h"
  "${PROJECT_SOURCE_DIR}/Transforms/*.h" "${PROJECT_SOURCE_DIR}/Transforms/*.cpp"
  "${PROJECT_SOURCE_DIR}/Events/*.h" "${PROJECT_SOURCE_DIR}/Events/*.cpp"
  "${PROJECT_SOURCE_DIR}/Lights/*.h" "${PROJECT_SOURCE_DIR}/Lights/*.cpp"
  "${PROJECT_SOURCE_DIR}/Shader/*.h" "${PROJECT_SOURCE_DIR}/Shader/*.cpp"
  "${PROJECT_SOURCE_DIR}/Texture/*.h" "${PROJECT_SOURCE_DIR}/Texture/*.cpp"
  "${PROJECT_SOURCE_DIR}/Curves/*.h" "${PROJECT_SOURCE_DIR}/Curves/*.cpp"
  "${PROJECT_SOURCE_DIR}/../../Libraries-src/soil/SOIL/*.h" "${PROJECT_SOURCE_DIR}/../../Libraries-src/soil/SOIL/*.c"
  )

add_executable (main
    ${SRC_FILES}
)

# Add include directory of SOIL
target_include_directories(main PUBLIC ../../Libraries-src/soil)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET main PROPERTY CXX_STANDARD 20)
endif()



# Copy assets if necessary

add_custom_target(copy_assets
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy-assets.cmake
)

add_dependencies(main copy_assets)




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
#
# target_include_directories(main PUBLIC ${GLU_INCLUDE_DIRS})
#
# target_link_libraries(main ${GLU_LIBRARY})


# GLEW
target_include_directories(main PUBLIC ../../Libraries-src/glew/include)

target_link_directories(main PUBLIC ../../Libraries-src/glew/lib)
target_link_libraries(main GLEW)


# AssImp
set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_BUILD_ZLIB OFF)
set(ASSIMP_INSTALL OFF)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF)

add_subdirectory(../../Libraries-src/assimp ../../Libraries-src/assimp)
add_dependencies(main assimp)

target_include_directories(main PUBLIC ../../Libraries-src/assimp/include)

target_link_libraries(main assimp)