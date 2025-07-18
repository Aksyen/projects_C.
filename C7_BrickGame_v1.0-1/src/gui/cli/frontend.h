#ifndef FRONTEND_H
#define FRONTEND_H

// Размеры игрового поля, с учетом отступов для отображения рамок и
// масштабирования
#define GAME_FIELD_N \
  (FIELD_N + 2)  // Высота игрового поля с добавлением отступов (по одной строке
                 // сверху и снизу).
#define GAME_FIELD_M \
  (FIELD_M * 3 + 2)  // Ширина игрового поля с учетом увеличения в 3 раза и
                     // добавления отступов для рамок.

// Параметры окна для стартового меню
#define START_MENU_N 8   // Высота окна стартового меню.
#define START_MENU_M 25  // Ширина окна стартового меню.

// Параметры окна для меню паузы
#define PAUSE_MENU_N 5   // Высота окна меню паузы.
#define PAUSE_MENU_M 25  // Ширина окна меню паузы.

// Параметры окна для завершения игры (победа или проигрыш)
#define FINISH_GAME_N 10  // Высота окна завершения игры.
#define FINISH_GAME_M 25  // Ширина окна завершения игры.

// Ширина окна с информацией о текущем состоянии игры
#define GAME_INFO_M 25  // Ширина окна с информацией о счете, уровне и т. д.

// Ширина окна с управлением
#define CONTROLS_M 24  // Ширина окна с подсказками по управлению.

// Отступы для игрового интерфейса (верхний и левый)
#define TOP_MARGIN 0  // Отступ сверху от начала экрана.
#define LEFT_MARGIN 0  // Отступ слева от начала экрана.

#include <ncurses.h>  // Включение библиотеки ncurses для работы с графическим интерфейсом в терминале.

#include "../../brick_game.h"  // Включение основного заголовочного файла с логикой игры и состоянием.

// Инициализация библиотеки ncurses
void initNcurses();

// Инициализация цветовых схем для отображения элементов интерфейса
void initColors();

// Основная функция рендеринга интерфейса игры. Она отображает игровое поле,
// информацию и соответствующие меню в зависимости от статуса игры.
void render(int status, bool win, GameInfo_t gi);

// Функция для отображения окна с подсказками по управлению
WINDOW *printControls();

// Отображение игрового поля
WINDOW *printGameField(GameInfo_t gi);

// Отображение стартового меню
void printStartMenu();

// Отображение меню паузы
void printPauseMenu();

// Отображение окна победы
void printWin(GameInfo_t gi);

// Отображение окна завершения игры (проигрыш)
void printGameOver(GameInfo_t gi);

// Отображение информации о текущем состоянии игры (счет, уровень, скорость)
WINDOW *printGameInfo(GameInfo_t gi);

// Отображение следующей фигуры (которая появится на поле)
void printNextFigure(WINDOW *info_window, GameInfo_t gi);

#endif
