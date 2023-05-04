cmake_minimum_required(VERSION 3.10)

project(randombs)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static -lpthread")


# Add directories for header files
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw-3.3.8/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glew-2.1.0/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glm-0.9.9.8
    #${CMAKE_CURRENT_SOURCE_DIR}/common
)

# Add directories for libraries
link_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw-3.3.8/lib-mingw-w64
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glew-2.1.0/lib/Release/x64
    #${CMAKE_CURRENT_SOURCE_DIR}/lib
    #${CMAKE_CURRENT_SOURCE_DIR}/shaders
)

file(GLOB SOURCES
    "src/*.cpp"
    #"shaders/*.vertexshader"
    #"shaders/*.fragmentshader"
    #${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.vertexshader
    #${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.fragmentshader
)

add_executable(randombs ${SOURCES})


# Link libraries
target_link_libraries(
    randombs
    opengl32
    glfw3
    glew32s
    #${CMAKE_CURRENT_SOURCE_DIR}/external/glew-2.1.0/lib/Release/x64/glew32s.lib
    # glm
    gdi32
)

set_property(TARGET randombs PROPERTY CXX_STANDARD 11)


