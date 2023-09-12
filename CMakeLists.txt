cmake_minimum_required(VERSION 3.26)
project(CHESS)

set(CMAKE_CXX_STANDARD 20)

add_executable(CHESS main.cpp
        ENGINE/GRAPHICS/texture.cpp
        ENGINE/GRAPHICS/shader.cpp
        ENGINE/GRAPHICS/resourceManager.cpp
        ENGINE/Board.cpp
        ENGINE/Piece.cpp
        Addons/glad/glad.c
        Addons/stb/stb.cpp)


target_include_directories(CHESS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

find_package(glfw3 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(CHESS PRIVATE ${CMAKE_LIBRARIES})

find_package(OpenGL REQUIRED)
target_link_libraries(CHESS PRIVATE
        glfw
        ${OPENGL_LIBRARIES}
)

include_directories(/opt/homebrew/Cellar/glm/0.9.9.8)

set(ASSIMP_ROOT "/opt/homebrew/Cellar/assimp/5.2.5" CACHE PATH "Path to Assimp installation directory")
find_package(assimp REQUIRED HINTS ${ASSIMP_ROOT})
include_directories(${ASSIMP_INCLUDE_DIRS})
target_link_libraries(CHESS PRIVATE  ${ASSIMP_LIBRARIES})

find_package(Freetype REQUIRED )
target_link_libraries(CHESS PRIVATE  Freetype::Freetype)

include_directories(${IMGUI_INCLUDE_DIRS})
target_link_libraries(CHESS PRIVATE ${IMGUI_LIBRARIES})

find_package(glfw3 REQUIRED)
target_link_libraries(CHESS PRIVATE glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(CHESS PRIVATE OpenGL::GL)


include_directories(libraries)
