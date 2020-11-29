cmake_minimum_required(VERSION 3.5)

project(task2_OX_game_osvn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(task2_OX_game_osvn main.cpp player_factory.h human_player.cpp
    human_player.h player_base.h player_base.cpp pc_trivial_player.cpp pc_trivial_player.h pc_smart_player.cpp pc_smart_player.h
    play_area.cpp play_area.h)

link_directories(${CMAKE_SOURCE_DIR}/libs/lib)
target_link_libraries(task2_OX_game_osvn ncursesw)
include_directories(${CMAKE_SOURCE_DIR}/libs/include/ncursesw)
