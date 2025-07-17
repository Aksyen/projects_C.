
#include "snakewidget.h"

namespace s21 {

/**
 * @brief Конструктор виджета.
 * @param parent Родительский виджет Qt (по умолчанию nullptr).
 */
SnakeWidget::SnakeWidget(QWidget *parent)
    : QWidget(parent), controller_(game_), timer_(new QTimer(this)) {
  setFixedSize(600, 440);

  controller_.HandleUserInput(UserAction_t::Start);
  lastUpdate_ = std::chrono::steady_clock::now();

  connect(timer_, &QTimer::timeout, this, [this]() {
    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdate_)
            .count() >= game_.GetSpeed()) {
      controller_.Tick();
      lastUpdate_ = now;
    }
    update();

    if (controller_.IsGameOver() || controller_.IsWin()) timer_->stop();
  });

  timer_->start(50);  // фиксированный FPS, игра обновляется по таймеру внутри
}

/**
 * @brief Отрисовка игрового интерфейса.
 * @param event Событие перерисовки (не используется).
 */
void SnakeWidget::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  auto info = controller_.GetGameInfo();
  DrawField(painter, info);
  DrawInfo(painter, info);
  DrawControls(painter);
}

/**
 * @brief Отображает игровое поле.
 *
 * Отрисовывает прямоугольное игровое поле, включая:
 * - чёрный фон,
 * - яблоко (красный круг),
 * - голову змейки (ярко-зелёный круг),
 * - тело змейки (тёмно-зелёные круги).
 *
 * @param painter Ссылка на объект QPainter для отрисовки.
 * @param info Структура с текущей информацией об игре (змейка, яблоко,
 * размеры).
 */
void SnakeWidget::DrawField(QPainter &painter, const SnakeInfo_t &info) {
  painter.setBrush(Qt::black);
  painter.drawRect(margin_, margin_, info.width * cellSize_,
                   info.height * cellSize_);

  painter.setBrush(QColor("#cc0000"));
  painter.setPen(Qt::NoPen);
  painter.drawEllipse(margin_ + info.apple.x * cellSize_,
                      margin_ + info.apple.y * cellSize_, cellSize_, cellSize_);

  if (!info.snake.empty()) {
    const Position &head = info.snake.front();
    painter.setBrush(QColor("#00ff00"));
    painter.drawEllipse(margin_ + head.x * cellSize_,
                        margin_ + head.y * cellSize_, cellSize_, cellSize_);
  }

  painter.setBrush(QColor("#007700"));
  for (size_t i = 1; i < info.snake.size(); ++i) {
    const Position &pos = info.snake[i];
    painter.drawEllipse(margin_ + pos.x * cellSize_,
                        margin_ + pos.y * cellSize_, cellSize_, cellSize_);
  }
}

/**
 * @brief Отображает информацию об игре.
 *
 * Выводит информацию о текущем счёте, уровне, рекорде и статусе игры
 * (Paused, Playing, Game Over, и т.д.) на правой панели.
 *
 * @param painter Ссылка на объект QPainter для отрисовки текста.
 * @param info Структура с текущими данными игры.
 */
void SnakeWidget::DrawInfo(QPainter &painter, const SnakeInfo_t &info) {
  int x = margin_ + info.width * cellSize_ + 20;
  int y = margin_;

  painter.setPen(Qt::black);
  QFont font("Courier", 10);
  painter.setFont(font);

  painter.drawText(x, y + 20, "🎮 Snake Game");
  painter.drawText(x, y + 50, QString("Score: %1").arg(info.score));
  painter.drawText(x, y + 70, QString("Level: %1").arg(info.level));
  painter.drawText(x, y + 90, QString("High:  %1").arg(info.high_score));
  painter.drawText(x, y + 120,
                   QString("Status: %1")
                       .arg(info.status == GameState::Paused     ? "Paused"
                            : info.status == GameState::Playing  ? "Playing"
                            : info.status == GameState::Win      ? "Win!"
                            : info.status == GameState::GameOver ? "Game Over"
                                                                 : "Initial"));
}

/**
 * @brief Отображает подсказки по управлению игрой.
 *
 * В нижней части окна отображаются клавиши управления:
 * стрелки — движение, Enter — рестарт, Space — пауза, Esc — выход.
 *
 * @param painter Ссылка на объект QPainter для отрисовки текста.
 */
void SnakeWidget::DrawControls(QPainter &painter) {
  int x = margin_;
  int y = margin_ + 420;
  painter.setPen(Qt::gray);
  painter.drawText(
      x, y, "↑ ↓ ← → — move | Space — pause | Enter — restart | Esc — exit");
}

/**
 * @brief Обработка нажатий клавиш.
 * @param event Событие клавиши.
 */
void SnakeWidget::keyPressEvent(QKeyEvent *event) {
  using enum UserAction_t;

  switch (event->key()) {
    case Qt::Key_Up:
      controller_.HandleUserInput(Up);
      break;
    case Qt::Key_Down:
      controller_.HandleUserInput(Down);
      break;
    case Qt::Key_Left:
      controller_.HandleUserInput(Left);
      break;
    case Qt::Key_Right:
      controller_.HandleUserInput(Right);
      break;
    case Qt::Key_Space:
      controller_.HandleUserInput(Pause);
      break;
    case Qt::Key_Enter:
    case Qt::Key_Return:
      controller_.HandleUserInput(Start);
      lastUpdate_ = std::chrono::steady_clock::now();
      timer_->start(50);
      break;
    case Qt::Key_Escape:
      close();
      break;
    default:
      break;
  }
}

}  // namespace s21
