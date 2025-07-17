/**
 * @file snake_console_view.hpp
 * @brief Консольный интерфейс игры "Змейка" с использованием ncurses.
 * @ingroup ConsoleInterface
 * @author lioncoco
 * @version 2.0
 * @date 2025-06-27
 */

/**
 * @defgroup ConsoleInterface Консольный интерфейс
 * @brief Реализация управления и отображения игр в терминале (ncurses).
 */

#ifndef S21_SNAKE_CONSOLE_VIEW_HPP
#define S21_SNAKE_CONSOLE_VIEW_HPP

#include <ncurses.h>

#include <chrono>
#include <thread>

#include "../../brick_game/snake/snake_controller.hpp"
#include "../../brick_game/snake/snake_game.hpp"

#define HEIGHT 22
#define FIELD_WIDTH 32
#define CONTROLS_WIDTH 24
#define INFO_WIDTH 25

namespace s21 {

/**
 * @class SnakeConsoleView
 * @ingroup ConsoleInterface
 * @brief Отвечает за отображение игры "Змейка" в терминале с помощью ncurses.
 *
 * Создаёт 3 окна: поле, панель управления и информационную панель.
 * Обрабатывает пользовательский ввод, рендерит змейку, яблоко, очки и меню.
 */
class SnakeConsoleView {
 public:
  SnakeConsoleView(SnakeController& controller);
  void Run();

 private:
  ///< Контроллер, управляющий логикой игры.
  SnakeController& controller_;

  void InitNcurses();
  void InitColors();
  void Render(WINDOW* controls_win, WINDOW* field_win, WINDOW* info_win);

  void DrawControls(WINDOW* win);
  void DrawField(WINDOW* win);
  void DrawInfo(WINDOW* win);

  void PrintStartMenu();
  void PrintPauseMenu();
  void PrintRestartMenu();

  void HandleInput(int ch);
};

}  // namespace s21

#endif  // S21_SNAKE_CONSOLE_VIEW_H
