cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)
project(update-studio)

find_package(Qt5Widgets 5.4 REQUIRED)

set(CMAKE_AUTOMOC ON)

add_subdirectory(studio)
add_subdirectory(updater)
