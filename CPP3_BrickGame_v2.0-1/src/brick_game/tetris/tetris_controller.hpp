/**
 * @file tetris_controller.hpp
 * @brief Контроллер игры "Тетрис" — связь между пользовательским вводом и
 * логикой игры.
 * @ingroup TetrisGame
 * @author lioncoco
 * @version 2.0
 * @date 2025-06-27
 */

/**
 * @defgroup TetrisGame Логика игры Тетрис
 * @brief Вся внутренняя реализация тетриса: состояние игры, поведение фигур,
 * поля, уровни.
 */

#ifndef TETRIS_CONTROLLER_HPP
#define TETRIS_CONTROLLER_HPP

extern "C" {
#include "backend_tetris.h"
}

namespace s21 {

/**
 * @class TetrisController
 * @ingroup TetrisGame
 * @brief Контроллер игры "Тетрис".
 *
 * Управляет состоянием игры, обрабатывает пользовательский ввод,
 * запускает обновления по таймеру, и обеспечивает доступ к информации
 * об игре для отображения в интерфейсе.
 */
class TetrisController {
 public:
  TetrisController();

  void HandleUserInput(UserAction_t action);
  void Tick();
  GameInfo_t GetGameInfo() const;
  void Restart();
  bool IsGameOver() const;
  bool IsWin() const;

 private:
  GameState_t *gs_;
};

}  // namespace s21

#endif  // TETRIS_CONTROLLER_HPP