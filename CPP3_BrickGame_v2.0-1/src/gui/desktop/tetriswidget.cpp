#include "tetriswidget.hpp"

namespace s21 {

/**
 * @brief Конструктор виджета.
 * @param parent Родительский виджет Qt (по умолчанию nullptr).
 */
TetrisWidget::TetrisWidget(QWidget *parent)
    : QWidget(parent), timer_(new QTimer(this)) {
  setFixedSize(600, 440);
  controller_.Restart();

  connect(timer_, &QTimer::timeout, this, &TetrisWidget::gameTick);
  timer_->start(50);
}

/**
 * @brief Обновляет игру по таймеру.
 *
 * Вызывает обновление логики, перерисовку и завершает игру при проигрыше или
 * победе.
 */
void TetrisWidget::gameTick() {
  controller_.Tick();
  update();
  if (controller_.IsGameOver() || controller_.IsWin()) {
    timer_->stop();
  }
}

/**
 * @brief Обрабатывает перерисовку виджета.
 * @param event Событие отрисовки (не используется).
 */
void TetrisWidget::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  GameInfo_t info = controller_.GetGameInfo();

  DrawField(painter, info);
  DrawNextFigure(painter, info);
  DrawInfo(painter, info);
  DrawControls(painter);

  freeGameInfo(&info);
}

/**
 * @brief Обрабатывает нажатия клавиш.
 * @param event Событие клавиатуры.
 */
void TetrisWidget::keyPressEvent(QKeyEvent *event) {
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
      controller_.Restart();
      timer_->start(50);
      break;
    case Qt::Key_Escape:
      close();
      break;
    default:
      break;
  }
}

/**
 * @brief Отрисовывает игровое поле.
 *
 * @param painter Объект для рисования.
 * @param info Структура с данными об игре.
 */
void TetrisWidget::DrawField(QPainter &painter, const GameInfo_t &info) {
  painter.setBrush(Qt::black);
  painter.drawRect(margin_, margin_, FIELD_M * cellSize_, FIELD_N * cellSize_);

  for (int i = 0; i < FIELD_N; ++i) {
    for (int j = 0; j < FIELD_M; ++j) {
      if (info.field[i][j] > 0) {
        painter.setBrush(GetFigureColor(info.field[i][j]));
        painter.drawRect(margin_ + j * cellSize_, margin_ + i * cellSize_,
                         cellSize_, cellSize_);
      }
    }
  }
}

/**
 * @brief Отрисовывает следующую фигуру.
 *
 * @param painter Объект для рисования.
 * @param info Структура с данными об игре.
 */
void TetrisWidget::DrawNextFigure(QPainter &painter, const GameInfo_t &info) {
  int x = margin_ + FIELD_M * cellSize_ + 30;
  int y = margin_;

  painter.setPen(Qt::black);
  painter.drawText(x, y + 20, "Next:");

  for (int i = 0; i < info.next_size; ++i) {
    for (int j = 0; j < info.next_size; ++j) {
      int type = info.next[i][j];
      if (type > 0) {
        painter.setBrush(GetFigureColor(type));
        painter.setPen(Qt::NoPen);
        painter.drawRect(x + j * cellSize_, y + 30 + i * cellSize_, cellSize_,
                         cellSize_);
      }
    }
  }
}

/**
 * @brief Отображает информацию об игре: очки, уровень, рекорд, статус.
 *
 * @param painter Объект для рисования.
 * @param info Структура с данными об игре.
 */
void TetrisWidget::DrawInfo(QPainter &painter, const GameInfo_t &info) {
  int x = margin_ + FIELD_M * cellSize_ + 30;
  int y = margin_ + 140;

  QFont font("Courier", 10);
  painter.setFont(font);
  painter.setPen(Qt::black);

  painter.drawText(x, y + 20, QString("Score: %1").arg(info.score));
  painter.drawText(x, y + 40, QString("Level: %1").arg(info.level));
  painter.drawText(x, y + 60, QString("High:  %1").arg(info.high_score));

  QString status = info.pause                 ? "Paused"
                   : controller_.IsWin()      ? "Win!"
                   : controller_.IsGameOver() ? "Game Over"
                                              : "Playing";
  painter.drawText(x, y + 90, QString("Status: %1").arg(status));
}

/**
 * @brief Отображает подсказки по управлению в нижней части окна.
 *
 * @param painter Объект для рисования.
 */
void TetrisWidget::DrawControls(QPainter &painter) {
  int x = margin_;
  int y = margin_ + FIELD_N * cellSize_ + 10;

  painter.setPen(Qt::gray);
  painter.drawText(
      x, y, "↑ ↓ ← → — move | Space — pause | Enter — restart | Esc — exit");
}

/**
 * @brief Возвращает цвет фигуры по её типу.
 *
 * @param figureType Числовой тип фигуры (1–8).
 * @return Цвет соответствующей фигуры.
 */
QColor TetrisWidget::GetFigureColor(int figureType) {
  switch (figureType) {
    case 1:
      return QColor("#ff0000");  // Red
    case 2:
      return QColor("#cc6600");  // Orange
    case 3:
      return QColor("#ffff00");  // Yellow
    case 4:
      return QColor("#ff00ff");  // Magenta
    case 5:
      return QColor("#00ff00");  // Green
    case 6:
      return QColor("#0000ff");  // Blue
    case 7:
      return QColor("#8000ff");  // Purple
    case 8:
      return QColor("#00ffff");  // Cyan
    default:
      return QColor(Qt::white);
  }
}

}  // namespace s21
