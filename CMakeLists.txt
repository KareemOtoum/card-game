cmake_minimum_required(VERSION 3.15...4.0)
project(
    higher_lower 
    VERSION 1.0
    LANGUAGES CXX
)

add_executable(game
    src/card.cpp
    src/deck.cpp
    src/game_state.cpp
    src/main.cpp
    src/terminal.cpp
)

target_include_directories(game PRIVATE include)

