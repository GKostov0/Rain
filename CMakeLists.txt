cmake_minimum_required(VERSION 4.2.0)

project(Rain
    VERSION 1.0.0
    DESCRIPTION "Space shooter game"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(RAIN_GAME_TARGET_NAME RainGame)

add_subdirectory(Rain)