cmake_minimum_required(VERSION 3.16)

project(snake LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# add_compile_options(-Wall -Wextra -Werror)

# include(GNUInstallDirs)
# install(TARGETS snake
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )


# add_library(snake
#     snake_game.cpp
#     snake_controller.cpp
# )

add_library(snake
    snake_game.cpp
    snake_game.hpp
    snake_controller.cpp
    snake_controller.hpp
)

target_include_directories(snake PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})