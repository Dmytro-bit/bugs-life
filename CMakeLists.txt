cmake_minimum_required(VERSION 3.30)
project(bug_life)

set(CMAKE_CXX_STANDARD 20)

add_executable(bug_life main.cpp
        Crawler.cpp
        Crawler.h
        Board.cpp
        Board.h)
