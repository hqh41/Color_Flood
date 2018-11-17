cmake_minimum_required(VERSION 3.8)
project(color_flood)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        ini_flood.h
        play.c)

add_executable(color_flood ${SOURCE_FILES})