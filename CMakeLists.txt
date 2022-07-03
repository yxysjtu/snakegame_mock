cmake_minimum_required(VERSION 3.17)
project(snakegame_mock)

set(CMAKE_CXX_STANDARD 14)

include_directories(snake_src_mock C:/Users/asus/Desktop/pdcurses_tutorial)
link_directories(C:/Users/asus/Desktop/pdcurses_tutorial)

add_executable(snakegame_mock
        snake_src_mock/game.cpp
        snake_src_mock/game.h
        snake_src_mock/main.cpp
        snake_src_mock/snake.cpp
        snake_src_mock/snake.h
        snake_src_mock/Food.cpp
        snake_src_mock/Food.h)

target_link_libraries(snakegame_mock
        pdcurses.lib
        )
