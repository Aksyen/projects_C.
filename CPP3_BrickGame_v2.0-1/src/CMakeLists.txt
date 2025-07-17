cmake_minimum_required(VERSION 3.16)

project(BrickGameV2 VERSION 2.0 LANGUAGES C CXX)

# Qt и автоматические инструменты
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Стандарты и флаги
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Werror)

# Найти Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Добавить подпроекты
add_subdirectory(brick_game/snake)
add_subdirectory(gui/desktop)
add_subdirectory(brick_game/tetris)

# Сборка основного исполняемого файла (main.cpp в корне)
qt_add_executable(BrickGameV2
    MANUAL_FINALIZATION
    main.cpp
)

# Линковка библиотек
target_link_libraries(BrickGameV2
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        snake
        desktop
        tetris
)

# Свойства и установка
set_target_properties(BrickGameV2 PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BrickGameV2)
endif()

# Установка (необязательный блок)
include(GNUInstallDirs)
install(TARGETS BrickGameV2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)