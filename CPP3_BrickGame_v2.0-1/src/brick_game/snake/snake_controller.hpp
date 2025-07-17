/**
 * @file snake_controller.hpp
 * @brief Контроллер управления игрой "Змейка" — обрабатывает действия игрока.
 * @ingroup SnakeGame
 * @author lioncoco
 * @version 2.0
 * @date 2025-06-27
 */

/**
 * @defgroup SnakeGame Логика игры Змейка
 * @brief Внутренняя реализация игры "Змейка" — поведение, состояние и правила.
 */

#ifndef S21_SNAKE_CONTROLLER_HPP
#define S21_SNAKE_CONTROLLER_HPP

#include "snake_game.hpp"

namespace s21 {

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/**
 * @class SnakeController
 * @ingroup SnakeGame
 * @brief Контроллер для управления игрой "Змейка".
 *
 * Принимает действия пользователя и управляет объектом SnakeGame,
 * изменяя направление, состояние и запуская обновление.
 */
class SnakeController {
 public:
  SnakeController(SnakeGame& game);

  void HandleUserInput(UserAction_t action);
  void Tick();  // вызывается по таймеру — обновляет модель
  SnakeInfo_t GetGameInfo() const;
  bool IsWin() const;
  bool IsGameOver() const;

 private:
  ///< Ссылка на объект логики игры.
  SnakeGame& game_;
};

}  // namespace s21

#endif  // S21_SNAKE_CONTROLLER_HPP
