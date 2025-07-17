/**
 * @file frontend.h
 * @brief Консольный интерфейс игры "Тетрис" на базе ncurses.
 * @ingroup ConsoleInterface
 * @author lioncoco
 * @version 2.0
 * @date 2025-06-27
 */

/**
 * @defgroup ConsoleInterface Консольный интерфейс
 * @brief Отображение игр в терминале с использованием библиотеки ncurses.
 */

#ifndef FRONTEND_H
#define FRONTEND_H

#include <ncurses.h>

#include "../../brick_game/tetris/backend_tetris.h"

/// @brief Высота игрового поля с рамками.
#define GAME_FIELD_N (FIELD_N + 2)

/// @brief Ширина игрового поля с рамками и масштабированием.
#define GAME_FIELD_M (FIELD_M * 3 + 2)

/// @brief Высота окна стартового меню.
#define START_MENU_N 8

/// @brief Ширина окна стартового меню.
#define START_MENU_M 25

/// @brief Высота окна меню паузы.
#define PAUSE_MENU_N 5

/// @brief Ширина окна меню паузы.
#define PAUSE_MENU_M 25

/// @brief Высота окна завершения игры (победа/проигрыш).
#define FINISH_GAME_N 10

/// @brief Ширина окна завершения игры (победа/проигрыш).
#define FINISH_GAME_M 25

/// @brief Ширина окна с игровой информацией.
#define GAME_INFO_M 25

/// @brief Ширина окна управления.
#define CONTROLS_M 24

/// @brief Верхний отступ интерфейса.
#define TOP_MARGIN 0

/// @brief Левый отступ интерфейса.
#define LEFT_MARGIN 0

/// @brief Код клавиши Escape.
#define KEY_ESC 27

/// @brief Код клавиши пробела.
#define KEY_SPACE 32

/// @brief Код клавиши 'q'.
#define KEY_Q 113

/// @brief Код клавиши 'z'.
#define KEY_Z 122

/**
 * @brief Инициализация библиотеки ncurses.
 *
 * Настраивает поведение терминала: ввод с клавиатуры, скрытие курсора,
 * неблокирующий режим, обработку специальных клавиш и событий мыши.
 */
void initNcurses();

/**
 * @brief Устанавливает цветовые схемы для всех элементов интерфейса.
 *
 * Настраивает цветовые пары для различных фигур и интерфейсных элементов.
 */
void initColors();

/**
 * @brief Основная функция отрисовки интерфейса.
 *
 * Отображает игровое поле, меню (старт, пауза, победа, проигрыш) и информацию
 * о текущем состоянии игры.
 *
 * @param status Текущий статус игры.
 * @param win Флаг победы.
 * @param gi Структура с информацией об игре.
 */
void render(int status, bool win, GameInfo_t gi);

/**
 * @brief Отображает окно с подсказками по управлению.
 * @return Указатель на созданное окно.
 */
WINDOW *printControls();

/**
 * @brief Отображает игровое поле с текущими фигурами.
 * @param gi Информация об игре.
 * @return Указатель на окно игрового поля.
 */
WINDOW *printGameField(GameInfo_t gi);

/**
 * @brief Обрабатывает ввод пользователя и преобразует его в действие.
 * @param ch Введённый символ или код клавиши.
 * @return Действие пользователя.
 */
UserAction_t getUserAction(int ch);

/**
 * @brief Отображает стартовое меню.
 */
void printStartMenu();

/**
 * @brief Отображает меню паузы.
 */
void printPauseMenu();

/**
 * @brief Отображает окно победы.
 * @param gi Информация об игре.
 */
void printWin(GameInfo_t gi);

/**
 * @brief Отображает окно окончания игры (проигрыша).
 * @param gi Информация об игре.
 */
void printGameOver(GameInfo_t gi);

/**
 * @brief Отображает информацию о счёте, уровне, скорости и следующей фигуре.
 * @param gi Информация об игре.
 * @return Указатель на окно информации.
 */
WINDOW *printGameInfo(GameInfo_t gi);

/**
 * @brief Отображает следующую фигуру в окне информации.
 * @param info_window Окно, в котором будет отрисована фигура.
 * @param gi Информация об игре.
 */
void printNextFigure(WINDOW *info_window, GameInfo_t gi);

#endif
