cmake_minimum_required(VERSION 3.22)
project(Hangman)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Hangman
        HangMan_2_2.cpp head.cpp)
