cmake_minimum_required(VERSION 3.16)

project(desktop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Werror)

# Источник всех файлов
set(SOURCES
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    snakewidget.cpp
    snakewidget.h
    tetriswidget.cpp
    tetriswidget.hpp
)

# Найти Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Создать библиотеку
add_library(desktop ${SOURCES})

# Инклуды и линковка
target_include_directories(desktop PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(desktop
    PUBLIC Qt6::Widgets
    PUBLIC snake
    PUBLIC tetris
)
