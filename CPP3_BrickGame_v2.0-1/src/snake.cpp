#include "brick_game/snake/snake_controller.hpp"
#include "brick_game/snake/snake_game.hpp"
#include "gui/cli/snake_console_view.hpp"

int main() {
  s21::SnakeGame game;
  s21::SnakeController controller(game);
  s21::SnakeConsoleView view(controller);

  view.Run();  // Запустить игру

  return 0;
}
