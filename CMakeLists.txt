cmake_minimum_required(VERSION 3.26)
project(CHESS)

set(CMAKE_CXX_STANDARD 20)

add_executable(CHESS main.cpp
        ENGINE/GRAPHICS/Texture/texture.cpp
        ENGINE/GRAPHICS/Shader/shader.cpp
        ENGINE/GRAPHICS/ResourceManager/resourceManager.cpp
        ENGINE/ENTITY/Board/Board.cpp
        ENGINE/ENTITY/Piece/Piece.cpp
        Addons/glad/glad.c
        Addons/stb/stb.cpp
        ENGINE/GRAPHICS/Renderer/SpriteRenderer.cpp
        ENGINE/IO/keyboard.cpp
        ENGINE/IO/mouse.cpp
        ENGINE/GRAPHICS/GameLevel/GameLevel.cpp
        ENGINE/GRAPHICS/GameLevel/GameObject.cpp
        ENGINE/ENTITY/Position/Position.hpp
        ENGINE/ENTITY/Types/Bishop.hpp
        ENGINE/ENTITY/Types/King.hpp
        ENGINE/ENTITY/Types/Knight.hpp
        ENGINE/ENTITY/Types/Pawn.hpp
        ENGINE/ENTITY/Types/Queen.hpp
        ENGINE/ENTITY/Types/Rook.hpp
        ENGINE/ENTITY/FENparser/FENparser.cpp
        ENGINE/ENTITY/MoveHandler/MoveHandler.cpp
        ENGINE/ENTITY/CheckDetector/CheckDetector.cpp)


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
