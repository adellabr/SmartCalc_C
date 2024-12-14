#ifndef MAINWINDOW_H
#define MAINWINDOW_H

extern "C" {
#include "../s21_SmartCalc.h"
}

#include <QMainWindow>
#include <QStandardItemModel>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  double x0, x1, y0, y1, h, X, Y;
  int N;
  QVector<double> x, y;

 private slots:
  void connections();
  void set_range();
  void digits_numbers();
  void on_pushButton_AC_clicked();
  void on_pushButton_eq_clicked();
  void on_pushButton_back_clicked();

  void on_pushButton_graph_clicked();
};
#endif  // MAINWINDOW_H
