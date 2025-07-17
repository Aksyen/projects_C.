#include "../brick_game/snake/snake_game.hpp"

#include <gtest/gtest.h>

#include "../brick_game/snake/snake_controller.hpp"

using namespace s21;

TEST(SnakeGameTest, StartInitializesCorrectly) {
  SnakeGame game;
  SnakeController controller(game);
  controller.HandleUserInput(UserAction_t::Start);
  auto info = controller.GetGameInfo();

  EXPECT_EQ(info.status, GameState::Playing);
  EXPECT_EQ(info.snake.size(), 4);
  EXPECT_EQ(info.level, 1);
  EXPECT_EQ(info.score, 0);
  EXPECT_EQ(info.speed, 1000);
}

TEST(SnakeGameTest, PauseAndResumeWorks) {
  SnakeGame game;
  SnakeController controller(game);

  controller.HandleUserInput(UserAction_t::Start);
  controller.HandleUserInput(UserAction_t::Pause);
  EXPECT_EQ(controller.GetGameInfo().status, GameState::Paused);

  controller.HandleUserInput(UserAction_t::Pause);
  EXPECT_EQ(controller.GetGameInfo().status, GameState::Playing);
}

TEST(SnakeGameTest, DirectionChangeValid_1) {
  SnakeGame game;
  SnakeController controller(game);

  controller.HandleUserInput(UserAction_t::Start);
  auto before = controller.GetGameInfo().snake.front();

  controller.HandleUserInput(UserAction_t::Left);
  controller.Tick();
  auto after = controller.GetGameInfo().snake.front();

  EXPECT_NE(before, after);
}

TEST(SnakeGameTest, DirectionChangeValid_2) {
  SnakeGame game;
  SnakeController controller(game);

  controller.HandleUserInput(UserAction_t::Start);
  auto before = controller.GetGameInfo().snake.front();

  controller.HandleUserInput(UserAction_t::Right);
  controller.Tick();
  auto after = controller.GetGameInfo().snake.front();

  EXPECT_NE(before, after);
}

TEST(SnakeGameTest, AppleEatenAndGrows) {
  SnakeGame game;
  SnakeController controller(game);

  controller.HandleUserInput(UserAction_t::Start);

  // Проверяем где голова
  auto info = controller.GetGameInfo();
  Position head = info.snake.front();

  Position apple_pos = head;
  apple_pos.y -= 1;
  game.SetAppleForTest(apple_pos);

  int before_size = info.snake.size();

  controller.HandleUserInput(UserAction_t::Up);
  controller.Tick();

  info = controller.GetGameInfo();
  EXPECT_GT(info.snake.size(), before_size);
  EXPECT_EQ(info.score, 1);
}

TEST(SnakeFSMTest, WinAfterGrowing) {
  SnakeGame game;
  SnakeController controller(game);

  controller.HandleUserInput(UserAction_t::Start);  // инициализация игры

  game.Grow_for_test();
  controller.Tick();

  EXPECT_EQ(controller.GetGameInfo().status, GameState::Win);
}

TEST(SnakeGameTest, GameOverOnWallCollision) {
  SnakeGame game;
  SnakeController controller(game);
  controller.HandleUserInput(UserAction_t::Start);

  controller.HandleUserInput(UserAction_t::Up);

  for (int i = 0; i < 30; ++i) {
    controller.Tick();
    if (controller.IsGameOver()) break;
  }

  EXPECT_TRUE(controller.IsGameOver());
}

TEST(SnakeGameTest, UpdateIgnoresWhenNotPlaying) {
  SnakeGame game;
  SnakeController controller(game);

  controller.Tick();
  EXPECT_EQ(controller.GetGameInfo().status, GameState::Initial);
}

TEST(SnakeGameTest, GetStatusInitiallyPlaying) {
  SnakeGame game;
  game.Start();
  EXPECT_EQ(game.GetStatus(), GameState::Playing);
}

TEST(SnakeGameTest, IsWinFalseInitially) {
  SnakeGame game;
  game.Start();
  EXPECT_FALSE(game.IsWin());
}

TEST(SnakeGameTest, GetSnakeNotEmptyAfterStart) {
  SnakeGame game;
  game.Start();
  EXPECT_FALSE(game.GetSnake().empty());
}

TEST(SnakeGameTest, GetAppleValidPosition) {
  SnakeGame game;
  game.Start();
  const Position& apple = game.GetApple();
  EXPECT_GE(apple.x, 0);
  EXPECT_GE(apple.y, 0);
}

TEST(SnakeGameTest, GetScoreInitiallyZero) {
  SnakeGame game;
  game.Start();
  EXPECT_EQ(game.GetScore(), 0);
}

TEST(SnakeGameTest, GetSpeedDefaultValue) {
  SnakeGame game;
  game.Start();
  EXPECT_GT(game.GetSpeed(), 0);
}

TEST(SnakeGameTest, GetHighScoreInitiallyZero) {
  SnakeGame game;
  game.Start();
  EXPECT_EQ(game.GetHighScore(), 0);
}

TEST(SnakeGameTest, GetLevelInitiallyOne) {
  SnakeGame game;
  game.Start();
  EXPECT_EQ(game.GetLevel(), 1);
}