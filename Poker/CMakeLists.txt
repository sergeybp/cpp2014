cmake_minimum_required(VERSION 2.8.4)
project(POKER)
INCLUDE_DIRECTORIES(${POKER_SOURCE_DIR})


add_executable(poker
main.cpp player/player.h
pokerController/pokerOn.h pokerController/pokerOn.cpp
cards/cards.h cards/cards.cpp
player/playerH.h player/playerH.cpp
table/table.h table/table.cpp
)


  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -g -std=c++0x")


target_link_libraries(poker)
