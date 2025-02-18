cmake_minimum_required(VERSION 3.28)
project(Game)

set(CMAKE_CXX_STANDARD 26)

add_executable(Game main.cpp
        src/State.cpp
        src/Sprite.cpp
        src/Music.cpp
        src/Game.cpp
        src/Vec2.cpp
        src/Rect.cpp
        src/Component.cpp
        src/GameObject.cpp
        src/Animation.cpp
        src/SpriteRenderer.cpp
        src/Zombie.cpp
        src/AnimationSetter.cpp
        src/TileSet.cpp
        src/TileMap.cpp
        src/Sound.cpp
        src/Resources.cpp
        src/InputManager.cpp
        src/Camera.cpp
        src/Character.cpp
        src/Gun.cpp
        src/Timer.cpp
        src/PlayerController.cpp
        src/Bullet.cpp
        src/Collider.cpp
        src/AIController.cpp
        src/Wave.cpp
        src/WaveSpawner.cpp
)

link_libraries(SDL2SDL2_imageSDL2_ttfSDL2_mixer)

include_directories(/usr/include/SDL2)
target_link_libraries(${PROJECT_NAME} SDL2 SDL2main SDL2_image SDL2_mixer)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/public DESTINATION ${CMAKE_CURRENT_BINARY_DIR})