/**
 * @file tetriswidget.hpp
 * @brief Qt-виджет для отображения игры "Тетрис".
 * @ingroup DesktopInterface
 * @author lioncoco
 * @version 2.0
 * @date 2025-06-27
 */

/**
 * @defgroup DesktopInterface Десктопный интерфейс
 * @brief Графический интерфейс игры с использованием Qt.
 */

#ifndef TETRISWIDGET_HPP
#define TETRISWIDGET_HPP

#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>

#include "../../brick_game/tetris/tetris_controller.hpp"

namespace s21 {

/**
 * @class TetrisWidget
 * @ingroup DesktopInterface
 * @brief Qt-виджет для игры "Тетрис".
 *
 * Отображает поле игры, следующую фигуру, информацию о счёте, уровне и
 * состоянии игры. Обрабатывает нажатия клавиш и обновляет игру через таймер.
 */
class TetrisWidget : public QWidget {
  Q_OBJECT

 public:
  explicit TetrisWidget(QWidget *parent = nullptr);

 protected:
  void paintEvent(QPaintEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

 private slots:
  void gameTick();

 private:
  void DrawField(QPainter &painter, const GameInfo_t &info);
  void DrawNextFigure(QPainter &painter, const GameInfo_t &info);
  void DrawInfo(QPainter &painter, const GameInfo_t &info);
  void DrawControls(QPainter &painter);
  QColor GetFigureColor(int figureType);

 private:
  TetrisController controller_;
  QTimer *timer_;
  int cellSize_ = 20;
  int margin_ = 20;
};

}  // namespace s21

#endif  // TETRIS_WIDGET_HPP