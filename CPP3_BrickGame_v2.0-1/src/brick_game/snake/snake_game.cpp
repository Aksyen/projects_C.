

#include "snake_game.hpp"

namespace s21 {

/// @brief Конструктор. Загружает рекорд и инициализирует параметры.
SnakeGame::SnakeGame()
    : current_dir_(Direction::Up),
      status_(GameState::Initial),
      score_(0),
      high_score_(LoadScore(high_score_path())),
      level_(1),
      speed_(1000),
      field_width_(10),
      field_height_(20) {
  std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

/// @brief Запускает новую игру.
void SnakeGame::Start() {
  snake_.clear();
  status_ = GameState::Playing;
  score_ = 0;
  level_ = 1;
  speed_ = 1000;

  // Начальная змейка из 4 блоков
  int start_x = field_width_ / 2;
  int start_y = field_height_ / 2;

  for (int i = 0; i < 4; ++i) {
    snake_.push_back({start_x, start_y + i});
  }

  current_dir_ = Direction::Up;
  SpawnApple();
}

/// @brief Ставит игру на паузу.
void SnakeGame::Pause() {
  if (status_ == GameState::Playing) {
    status_ = GameState::Paused;
  }
}

/// @brief Возобновляет игру после паузы
void SnakeGame::Resume() {
  if (status_ == GameState::Paused) {
    status_ = GameState::Playing;
  }
}

/// @brief Обновляет игру — перемещает змейку, проверяет столкновения и еду.
void SnakeGame::Update() {
  if (status_ != GameState::Playing) {
    return;
  }

  Move();
}

/// @brief Перемещает змейку на 1 шаг. Увеличивает длину змейки.
void SnakeGame::Move() {
  if (snake_.empty()) {
    return;
  }

  Position head = snake_.front();
  Position new_head = head;

  switch (current_dir_) {
    case Direction::Up:
      new_head.y -= 1;
      break;
    case Direction::Down:
      new_head.y += 1;
      break;
    case Direction::Left:
      new_head.x -= 1;
      break;
    case Direction::Right:
      new_head.x += 1;
      break;
  }

  if (CheckCollision(new_head)) {
    status_ = GameState::GameOver;
    return;
  }

  snake_.insert(snake_.begin(), new_head);

  if (new_head.x == apple_.x && new_head.y == apple_.y) {
    // std::cout << "🍏 Apple eaten at (" << apple_.x << "," << apple_.y <<
    // ")\n";
    Grow();
    SpawnApple();
  } else {
    snake_.pop_back();  // Просто движемся без роста
  }

  if (snake_.size() == 200) {
    status_ = GameState::Win;
  }
}

/// @brief Меняет направление движения змейки.
/// @param new_dir Новое направление.
void SnakeGame::ChangeDirection(Direction new_dir) {
  // Разрешить поворот только налево или направо относительно текущего
  // направления
  if (current_dir_ == new_dir) {
    current_dir_ = new_dir;
    Update();
  }

  if ((current_dir_ == Direction::Up &&
       (new_dir == Direction::Left || new_dir == Direction::Right)) ||
      (current_dir_ == Direction::Down &&
       (new_dir == Direction::Left || new_dir == Direction::Right)) ||
      (current_dir_ == Direction::Left &&
       (new_dir == Direction::Up || new_dir == Direction::Down)) ||
      (current_dir_ == Direction::Right &&
       (new_dir == Direction::Up || new_dir == Direction::Down))) {
    current_dir_ = new_dir;
  }
}

/// @brief Генерирует новое яблоко на поле.
void SnakeGame::SpawnApple() {
  bool valid = false;

  while (!valid) {
    int x = std::rand() % field_width_;
    int y = std::rand() % field_height_;
    Position new_apple = {x, y};

    valid = std::find(snake_.begin(), snake_.end(), new_apple) == snake_.end();
    if (valid) {
      apple_ = new_apple;
    }
  }
  // std::cout << "🍏 SpawnApple (" << apple_.x << "," << apple_.y << ")\n";
}

/// @brief Проверка на столкновение.
/// @param pos Новая позиция головы.
/// @return true — если есть столкновение.
bool SnakeGame::CheckCollision(const Position& pos) const {
  if (pos.x < 0 || pos.x >= field_width_ || pos.y < 0 ||
      pos.y >= field_height_) {
    return true;  // Столкновение с границей
  }

  return std::find(snake_.begin(), snake_.end(), pos) !=
         snake_.end();  // Столкновение с самой собой
}

/// @brief Обновляет счёт и уровень.
void SnakeGame::Grow() {
  score_ += 1;

  if (score_ > high_score_) {
    high_score_ = score_;
    SaveScore(high_score_, high_score_path());
  }

  if (score_ % 5 == 0 && level_ < 10) {
    level_++;
    speed_ = std::max(100, speed_ - 90);  // Увеличение скорости
  }
}

/// @brief Тестовая функция — моментально почти выигрывает игру.
void SnakeGame::Grow_for_test() {
  score_ = 196;
  if (!snake_.empty()) {
    while (snake_.size() < 200) {
      snake_.push_back(snake_.back());  // безопасное удлинение
    }
  }
}

///< @return true — если игра окончена.
bool SnakeGame::IsGameOver() const { return status_ == GameState::GameOver; }

///< @return true — если достигнута победа.
bool SnakeGame::IsWin() const { return status_ == GameState::Win; }

///< @return Вектор клеток змейки.
const std::vector<Position>& SnakeGame::GetSnake() const { return snake_; }

///< @return Позиция яблока.
const Position& SnakeGame::GetApple() const { return apple_; }

///< @return Текущее состояние игры.
GameState SnakeGame::GetStatus() const { return status_; }

///< @return Текущий счёт.
int SnakeGame::GetScore() const { return score_; }

///< @return Скорость (мс между шагами).
int SnakeGame::GetSpeed() const { return speed_; }

///< @return Рекорд.
int SnakeGame::GetHighScore() const { return high_score_; }

///< @return Уровень.
int SnakeGame::GetLevel() const { return level_; }

/// @brief Возвращает информацию об игре для отображения.
SnakeInfo_t SnakeGame::GetInfo() const {
  return SnakeInfo_t{
      .snake = snake_,
      .apple = apple_,
      .status = status_,
      .score = score_,
      .high_score = high_score_,
      .level = level_,
      .speed = speed_,
      .width = field_width_,
      .height = field_height_,
  };
}

/**
 * @brief Сохраняет счет игрока в файл.
 * @param score Значение счета.
 * @param file_name Имя файла для сохранения.
 */
void SnakeGame::SaveScore(int score, const std::string& file_name) {
  std::ofstream file(file_name);
  if (file.is_open()) {
    file << score;
    file.close();
  }
}

/**
 * @brief Загружает сохраненный счет из файла.
 * @param file_name Имя файла для загрузки.
 * @return Загруженный счет (0, если файл отсутствует или поврежден).
 */
int SnakeGame::LoadScore(const std::string& file_name) {
  int score = 0;
  std::ifstream file(file_name);
  if (file.is_open()) {
    file >> score;
    file.close();
  }
  return score;
}

/// @brief Возвращает путь к файлу сохранения рекорда.
std::string SnakeGame::high_score_path() {
  // Путь по умолчанию
  std::filesystem::path install_path = "build";

  // Пытаемся прочитать путь из файла
  std::ifstream path_file("install_path.txt");
  if (path_file) {
    std::string path_from_file;
    if (std::getline(path_file, path_from_file)) {
      install_path = path_from_file;
    }
  }

  // Создаем полный путь к файлу high_score.txt
  std::filesystem::path high_score_path = install_path / "high_score_snake.txt";

  return high_score_path.string();
}

/// @brief Устанавливает позицию яблока (для тестов).
/// @param pos Позиция яблока.
void SnakeGame::SetAppleForTest(const Position& pos) {
  apple_ = pos;
  // std::cout << "🍏 Test apple set to (" << apple_.x << "," << apple_.y <<
  // ")\n";
}

}  // namespace s21
