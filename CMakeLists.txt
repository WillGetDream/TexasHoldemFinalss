cmake_minimum_required(VERSION 3.14)
project(TexasHoldem)

set(CMAKE_CXX_STANDARD 14)

add_executable(TexasHoldem main.cpp Player.cpp Player.h processControler.cpp Colors.h Utils.cpp Utils.h Position.h Card.h Card.cpp DeckOfCards.cpp DeckOfCards.h)