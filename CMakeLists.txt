cmake_minimum_required(VERSION 3.24)
project(BallJump)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_INCLUDE_DIR "D:\\SDL2-devel-2.30.1-VC\\SDL2-2.30.1\\include")
set(SDL2_IMAGE_INCLUDE_DIR "D:\\SDL2_image-2.0.1\\include")
set(SDL2_LIB_DIR "D:\\SDL2-devel-2.30.1-VC\\SDL2-2.30.1\\lib\\x64")
set(SDL2_IMAGE_LIB_DIR "D:\\SDL2_image-2.0.1\\lib\\x64")

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
add_executable(${PROJECT_NAME} main.cpp
        Game.cpp
        Game.h
        TextureManager.cpp
        TextureManager.h
        GameObject.cpp
        GameObject.h
        Map.cpp
        Map.h)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_DIR}/SDL2.lib ${SDL2_LIB_DIR}/SDL2main.lib)
target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIB_DIR}/SDL2_image.lib)