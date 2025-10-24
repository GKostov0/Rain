cmake_minimum_required(VERSION 3.29.5)

project(Rain
    VERSION 1.0.0
    DESCRIPTION "Space shooter game"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(RAIN_ENGINE_TARGET_NAME RainEngine)
set(RAIN_GAME_TARGET_NAME RainGame)

add_subdirectory(RainEngine)
add_subdirectory(RainGame)