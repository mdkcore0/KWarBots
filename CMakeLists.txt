project (kwarbots)

cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED) 
find_package(KDE4 REQUIRED)
include_directories(${KDE4_INCLUDES})

add_subdirectory(src)

