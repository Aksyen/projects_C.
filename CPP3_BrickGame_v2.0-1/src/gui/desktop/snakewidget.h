/**
 * @file snakewidget.h
 * @brief Виджет Qt для игры "Змейка". Отображает поле, счёт, управление.
 * @ingroup DesktopInterface
 * @author lioncoco
 * @version 2.0
 * @date 2025-06-27
 */

/**
 * @defgroup DesktopInterface Десктопный интерфейс
 * @brief Графический интерфейс игры с использованием Qt.
 */

#ifndef SNAKEWIDGET_H
#define SNAKEWIDGET_H

#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>

#include "snake_controller.hpp"
#include "snake_game.hpp"

namespace s21 {

/**
 * @class SnakeWidget
 * @ingroup DesktopInterface
 * @brief Qt-виджет для игры "Змейка".
 *
 * Отвечает за отображение поля игры, информации, клавиш управления
 * и обработку ввода с клавиатуры. Управляет запуском и обновлением игры
 * через таймер и взаимодействует с SnakeController.
 */
class SnakeWidget : public QWidget {
  Q_OBJECT

 public:
  explicit SnakeWidget(QWidget *parent = nullptr);

 protected:
  void paintEvent(QPaintEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

 private:
  SnakeGame game_;
  SnakeController controller_;
  std::chrono::steady_clock::time_point lastUpdate_;
  QTimer *timer_;
  int cellSize_ = 20;
  int margin_ = 10;

  void InitGame();
  void DrawField(QPainter &painter, const SnakeInfo_t &info);
  void DrawInfo(QPainter &painter, const SnakeInfo_t &info);
  void DrawControls(QPainter &painter);
};

}  // namespace s21

#endif  // SNAKEWIDGET_H