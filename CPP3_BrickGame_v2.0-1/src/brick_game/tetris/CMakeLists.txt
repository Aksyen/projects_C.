cmake_minimum_required(VERSION 3.16)

project(tetris LANGUAGES C)

# include(GNUInstallDirs)
# install(TARGETS tetris
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )

add_library(tetris
    backend_tetris.c
    backend_tetris.h
    tetris_controller.cpp
    tetris_controller.hpp

)

target_include_directories(tetris PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
