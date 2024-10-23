cmake_minimum_required(VERSION 3.28)
project(Game)

set(CMAKE_CXX_STANDARD 26)

add_executable(Game main.cpp
        src/State.cpp
        include/State.h
        src/Sprite.cpp
        include/Sprite.h
        src/Music.cpp
        include/Music.h
        src/Game.cpp
        include/Game.h)

link_libraries(SDL2SDL2_imageSDL2_ttfSDL2_mixer)

include_directories(/usr/include/SDL2)
target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2_image SDL2_mixer)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/public DESTINATION ${CMAKE_CURRENT_BINARY_DIR})