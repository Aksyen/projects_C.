/**
 * @file snake_game.hpp
 * @brief Логика игры "Змейка": движение, столкновения, рост, очки и победа.
 * @ingroup SnakeGame
 * @author lioncoco
 * @version 2.0
 * @date 2025-06-27
 */

/**
 * @defgroup SnakeGame Логика игры Змейка
 * @brief Внутренняя реализация игры "Змейка" — поведение, состояние и правила.
 */

#ifndef S21_SNAKE_GAME_HPP
#define S21_SNAKE_GAME_HPP

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

/**
 * @class SnakeGame
 * @ingroup SnakeGame
 * @brief Реализация логики игры "Змейка".
 *
 * Отвечает за текущее состояние игры, передвижение змейки,
 * генерацию яблок, обработку столкновений, счёт и уровни.
 */
namespace s21 {

enum class GameState { Initial, Playing, Paused, Win, GameOver };

enum class Direction { Up, Down, Left, Right };

struct Position {
  int x;
  int y;

  Position() = default;
  Position(int x_, int y_) : x(x_), y(y_) {}
  Position(const Position& other) : Position(other.x, other.y) {}
  Position& operator=(const Position& right) {
    x = right.x;
    y = right.y;
    return *this;
  }
  bool operator==(const Position& other) const {
    return x == other.x && y == other.y;
  }
};

struct SnakeInfo_t {
  std::vector<Position> snake;
  Position apple;
  GameState status;
  int score;
  int high_score;
  int level;
  int speed;
  int width;
  int height;
};

class SnakeGame {
 public:
  SnakeGame();

  void Start();
  void Pause();
  void Resume();
  void Move();
  void ChangeDirection(Direction new_dir);

  void Update();  // Вызов по таймеру
  bool IsGameOver() const;
  bool IsWin() const;

  // --- Геттеры статуса ---
  const std::vector<Position>& GetSnake() const;
  const Position& GetApple() const;
  GameState GetStatus() const;
  int GetScore() const;
  int GetSpeed() const;
  int GetHighScore() const;
  int GetLevel() const;
  void SetTemporaryBoost();
  SnakeInfo_t GetInfo() const;

  void SetAppleForTest(const Position& pos);
  void Grow_for_test();

 private:
  void SpawnApple();
  bool CheckCollision(const Position& pos) const;
  void Grow();
  void SaveScore(int score, const std::string& file_name);
  int LoadScore(const std::string& file_name);
  std::string high_score_path();

  std::vector<Position> snake_;
  Direction current_dir_;
  Position apple_;
  GameState status_;
  int score_;
  int high_score_;
  int level_;
  int speed_;  // в миллисекундах
  int field_width_;
  int field_height_;
};

}  // namespace s21

#endif  // SNAKE_GAME_HPP