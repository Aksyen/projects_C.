
#include "snake_controller.hpp"

namespace s21 {

/**
 * @brief Конструктор контроллера.
 * @param game Ссылка на объект игры SnakeGame.
 */
SnakeController::SnakeController(SnakeGame& game) : game_(game) {}

/**
 * @brief Обрабатывает действие пользователя.
 * @param action Действие пользователя (направление, пауза, старт и т.д.).
 */
void SnakeController::HandleUserInput(UserAction_t action) {
  switch (action) {
    case Left:
      game_.ChangeDirection(Direction::Left);
      break;
    case Right:
      game_.ChangeDirection(Direction::Right);
      break;
    case Up:
      game_.ChangeDirection(Direction::Up);
      break;
    case Down:
      game_.ChangeDirection(Direction::Down);
      break;
    case Pause:
      if (game_.GetStatus() == GameState::Playing)
        game_.Pause();
      else if (game_.GetStatus() == GameState::Paused)
        game_.Resume();
      break;
    case Start:
      game_.Start();
      break;
    case Action:
    case Terminate:
      break;
  }
}

/// @brief Выполняет обновление игры по таймеру (один тик).
void SnakeController::Tick() {
  if (game_.GetStatus() == GameState::Playing) {
    game_.Update();
  }
}

/**
 * @brief Возвращает информацию о текущем состоянии игры.
 * @return Структура с информацией об игре.
 */
SnakeInfo_t SnakeController::GetGameInfo() const { return game_.GetInfo(); }

/**
 * @brief Проверяет, завершилась ли игра победой.
 * @return true — если победа, иначе false.
 */
bool SnakeController::IsWin() const { return game_.IsWin(); }

/**
 * @brief Проверяет, завершилась ли игра проигрышем.
 * @return true — если игра окончена, иначе false.
 */
bool SnakeController::IsGameOver() const { return game_.IsGameOver(); }

}  // namespace s21
