#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_tetrisButton_clicked() {
  // QMessageBox::information(this, "Tetris", "Здесь будет запуск Тетриса!");
  auto *tetris = new TetrisWidget;
  tetris->setAttribute(Qt::WA_DeleteOnClose);
  tetris->show();
  this->hide();
}

void MainWindow::on_snakeButton_clicked() {
  // QMessageBox::information(this, "Snake", "Здесь будет запуск Змейки!");
  auto *snake = new SnakeWidget;
  snake->setAttribute(Qt::WA_DeleteOnClose);
  snake->show();
  this->hide();  // пока просто прячем главное окно
}

void MainWindow::on_exitButton_clicked() { close(); }
}  // namespace s21