#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "snakewidget.h"
#include "tetriswidget.hpp"
// #include "./ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_tetrisButton_clicked();

  void on_snakeButton_clicked();

  void on_exitButton_clicked();

 private:
  Ui::MainWindow *ui;
};
}  // namespace s21
#endif  // MAINWINDOW_H