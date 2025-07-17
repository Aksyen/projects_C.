#include "tetris_controller.hpp"

namespace s21 {

/**
 * @brief Конструктор контроллера.
 *
 * Инициализирует игру и запускает стартовое состояние.
 */
TetrisController::TetrisController() {
  gs_ = getGameState();
  initGame();
  userInput(gs_, Start);
}

/**
 * @brief Перезапускает игру.
 *
 * Повторно инициализирует игровое состояние и запускает игру заново.
 */
void TetrisController::Restart() {
  initGame();
  userInput(gs_, Start);
}

/**
 * @brief Обрабатывает действие пользователя.
 * @param action Действие (влево, вправо, поворот, падение и т.д.).
 */
void TetrisController::HandleUserInput(UserAction_t action) {
  userInput(gs_, action);
}

/**
 * @brief Выполняет один "тик" игры.
 *
 * Проверяет таймер и FSM (конечный автомат состояний) и обновляет игру.
 */
void TetrisController::Tick() {
  if (gs_->pause || !gs_->is_playing) return;

  if (timer(gs_, gs_->speed)) {
    userInput(gs_, Down);
  }

  // Обработка FSM переходов
  while (true) {
    switch (gs_->status) {
      case Attaching:
        attachFigure(gs_);
        break;
      case Spawn:
        spawnFigure(gs_);
        break;
      case Shifting:
        moveDown(gs_);
        break;
      default:
        return;
    }
  }
}

/**
 * @brief Получает актуальную информацию об игре.
 * @return Структура с данными: поле, очки, следующая фигура и т.д.
 */
GameInfo_t TetrisController::GetGameInfo() const {
  return updateCurrentState(gs_);
}

/**
 * @brief Проверяет, завершена ли игра поражением.
 * @return true — поражение, false — игра продолжается.
 */
bool TetrisController::IsGameOver() const { return gs_->status == GameOver; }

/**
 * @brief Проверяет, завершена ли игра победой.
 * @return true — победа, false — нет.
 */
bool TetrisController::IsWin() const { return gs_->win; }

}  // namespace s21
